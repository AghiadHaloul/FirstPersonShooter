﻿#include "Renderer.h"
//#include "Application Manager/ApplicationManager.h"
#include "ShaderProgram/SimpleShaderProgram.h"

 
SimpleShaderProgram simpleshader;




Renderer::Renderer()
{
 
 this->Initialize();   
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	Enemy::EnemyModel = unique_ptr<CMD2Model>(new CMD2Model());
	this->GameOver = false; 


	Game_SkyBox = unique_ptr<SkyBox> (new SkyBox()); 
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) Game_SkyBox.get());
	
	
	hero = unique_ptr<Hero>(new Hero(vec3(3,2,0),vec3(0,0,-1),100));
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) hero.get());
	
	if (StaticComponent::Current_Level == StaticComponent::Level1)
		Firstlevel = unique_ptr<Level1>(new Level1());
	else if (StaticComponent::Current_Level == StaticComponent::Level2)
		Secondlevel = unique_ptr<Level2>(new Level2());

	Initialize_CrossHair();


	initText2D("Holstein.DDS");
	shader.LoadProgram();
	animatedModelShader.LoadProgram();
	simpleshader.LoadProgram();
	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	
	float val = 150;
	lightPositions.push_back(vec3(-val,val,-val));
	lightPositions.push_back(vec3(val,val,-val));
	lightPositions.push_back(vec3(val,val,val));
	lightPositions.push_back(vec3(-val,val,val));
	vec3 scenecolor;
	if (StaticComponent::Current_Level == StaticComponent::Level1){
	 scenecolor = vec3(1,0.839,0.6666);
	lightcolors.push_back(scenecolor);
	lightcolors.push_back(scenecolor);
	lightcolors.push_back(scenecolor);
	lightcolors.push_back(scenecolor);
	}
	if (StaticComponent::Current_Level == StaticComponent::Level2){
		//scenecolor = vec3(0.2509,0.58823,1);
		scenecolor = vec3(0.83,0.92,1);
		lightcolors.push_back(scenecolor);
		lightcolors.push_back(scenecolor);
		lightcolors.push_back(scenecolor);
		lightcolors.push_back(scenecolor);
	}
	//setup the light position.
	shader.UseProgram();
	shader.BindLightColors(lightcolors);
	shader.BindLightPositions(lightPositions);
	//setup the ambient light component.
	ambientLight = glm::vec3(0.1,0.1,0.1);
	shader.BindAmbientLight(&ambientLight[0]);
	//setup the eye position.
	shader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);


	//////////////////////////////////////////////////////////////////////////
	animatedModelShader.UseProgram();
	//setup the ambient light component.
	shader.BindLightColors(lightcolors);
	animatedModelShader.BindLightPositions(lightPositions);
	//setup the ambient light component.
	ambientLight = glm::vec3(0.1,0.1,0.1);
	animatedModelShader.BindAmbientLight(&ambientLight[0]);
	//setup the eye position.
	animatedModelShader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);

	StaticComponent::PlayingTime = 0;
   
}


void Renderer::Initialize_CrossHair()
{
	///cross hair
	CorssModel = unique_ptr<TexturedModel>(new TexturedModel("data/textures/cross.png",27));

	CorssModel->VertexData.push_back(glm::vec3(-0.1f, -0.1f, 0.0f));
	CorssModel->VertexData.push_back(glm::vec3(0.1f ,-0.1f ,0.0f));
	CorssModel->VertexData.push_back(glm::vec3( 0.1f ,0.1f, 0.0f));
	CorssModel->VertexData.push_back(glm::vec3( -0.1f , 0.1f, 0.0f));

	CorssModel->UVData.push_back(glm::vec2(0.0f,1.0f));
	CorssModel->UVData.push_back(glm::vec2(1.0f,1.0f));
	CorssModel->UVData.push_back(glm::vec2(1.0f,0.0f));
	CorssModel->UVData.push_back(glm::vec2(0.0f,0.0f));

	//first triangle.
	CorssModel->IndicesData.push_back(0);
	CorssModel->IndicesData.push_back(1);
	CorssModel->IndicesData.push_back(3);
	//second triangle.
	CorssModel->IndicesData.push_back(1);
	CorssModel->IndicesData.push_back(2);
	CorssModel->IndicesData.push_back(3);
	CorssModel->Initialize();
	
}

void Renderer::Draw()
{		
	    glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UseProgram();
		
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glm::mat4 VP = hero->HeroCam->GetProjectionMatrix() * hero->HeroCam->GetViewMatrix();
		//shader.BindVPMatrix(&VP[0][0]);	
		
		Game_SkyBox->Render(&shader,VP);
		hero->Render(&shader,VP); //render nothing till now	
		
		if (StaticComponent::Current_Level == StaticComponent::Level1)
			Firstlevel->Render(&shader,&animatedModelShader,VP);
		else if (StaticComponent::Current_Level == StaticComponent::Level2)
			 Secondlevel->Render(&shader,&animatedModelShader,VP);

		StaticComponent::sceneBullets->Render(&shader,VP);
		
		glDisable(GL_DEPTH_TEST);
        
		Draw_CrossHair(); 
        DrawText();

}


void Renderer::DrawText()
{
	printText2D("HP",0,550,40);
	char health[100];
	itoa(hero->GetHealth(),health,10);
	printText2D(health,100,550,40);
	
	printText2D("time ",600,550,40);
	char playtime[100];
	sprintf(playtime, "%f", StaticComponent::PlayingTime);
	printText2D(playtime,550,500,40);
}

void Renderer::Draw_CrossHair()
{
	simpleshader.UseProgram();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CorssModel->Draw();
	glDisable(GL_BLEND);
}

void Renderer::Cleanup()
{
	StaticComponent::collisionManager->Cleanup();
	StaticComponent::sceneBullets->Cleanup();
   shader.CleanUp();
   animatedModelShader.CleanUp();
}

void Renderer::Update(double deltaTime)
{
	StaticComponent::PlayingTime += (deltaTime/1000);

	//reset the pressed key.
	StaticComponent::collisionManager->UpdateCollisions();
	hero->Update(deltaTime/1000); // update nothing till now
	
	if (StaticComponent::Current_Level == StaticComponent::Level1)
		Firstlevel->Update(deltaTime/1000);
	else if (StaticComponent::Current_Level == StaticComponent::Level2)
		Secondlevel->Update(deltaTime/1000);

	StaticComponent::sceneBullets->Update(deltaTime/1000);
	this->GameOver = hero->GetIsdestroied();
}

void Renderer::HandleKeyboardInput(int key)
{
    
	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		hero->Walk_Forward();
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		hero->Walk_Backward();
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		hero->Straf_Right();
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		hero->Straf_Left();
		break;

		// Moving up
	case GLFW_KEY_R:
		//hero->HeroCam->Fly(3);
		break;

		// Moving down
	case GLFW_KEY_F:
		//hero->HeroCam->Fly(-3);
		break;

	case GLFW_KEY_SPACE:
		StaticComponent::soundEngine->StartBackMusic("music/switch.wav");
		hero->Fire();
		break;
	
	default:
		break;
	}
	//update the eye position uniform.
	shader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);
    animatedModelShader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);
}

void Renderer::HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked)
{	
	hero->Yaw(deltaX);
	hero->Pitch(deltaY);
	//update the eye position uniform.
	shader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);
	animatedModelShader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);
	if(LeftBtn_clicked){
		StaticComponent::soundEngine->StartBackMusic("music/firesound.wav");
        hero->Fire();
	}
}

