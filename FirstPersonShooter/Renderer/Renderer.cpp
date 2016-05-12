#include "Renderer.h"
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
	//soundEngine = unique_ptr<SoundEngine>(new SoundEngine());
	//soundEngine->StartBackMusic("strings2.wav");
    this->GameOver = false;
	Game_SkyBox = unique_ptr<SkyBox> (new SkyBox(100.0f)); 
	Game_SkyBox->Initialize();

	hero = unique_ptr<Hero>(new Hero(vec3(3,-98,0),vec3(0,0,-1),Game_SkyBox->Unitsize));
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) hero.get());

	Firstlevel = unique_ptr<Level1>(new Level1());
	Initialize_CrossHair();


	initText2D("Holstein.DDS");
	shader.LoadProgram();
	animatedModelShader.LoadProgram();
	simpleshader.LoadProgram();
	shader.UseProgram();
	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	lightPosition = glm::vec3(0,-50,0);
	shader.BindLightPosition(&lightPosition[0]);
	//setup the ambient light component.
	ambientLight = glm::vec3(0.1,0.1,0.1);
	shader.BindAmbientLight(&ambientLight[0]);
	//setup the eye position.
	shader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);


	//////////////////////////////////////////////////////////////////////////
	animatedModelShader.UseProgram();
	lightPosition = glm::vec3(1.0,0.25,0.0);
	//setup the ambient light component.
	animatedModelShader.BindLightPosition(&lightPosition[0]);
	//setup the ambient light component.
	ambientLight = glm::vec3(0.5,0.5,0.5);

	animatedModelShader.BindAmbientLight(&ambientLight[0]);
	//setup the eye position.
	animatedModelShader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);

   
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
		shader.BindVPMatrix(&VP[0][0]);	
		Game_SkyBox->Draw(shader);
		
		hero->Render(&shader,VP); //render nothing till now	
		
		Firstlevel->Render(&shader,&animatedModelShader,VP);
	    StaticComponent::sceneBullets->Render(&shader,VP);
		glDisable(GL_DEPTH_TEST);
        Draw_CrossHair(); 
        DrawText();

}


void Renderer::DrawText()
{
	char health[100];
	itoa(hero->GetHealth(),health,10);
	printText2D("HP",0,550,40);
	printText2D(health,100,550,40);
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
   shader.CleanUp();
   animatedModelShader.CleanUp();
}

void Renderer::Update(double deltaTime)
{
	//reset the pressed key.
	StaticComponent::collisionManager->UpdateCollisions();
	hero->Update(deltaTime/1000); // update nothing till now
	Firstlevel->Update(deltaTime/1000);
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
		hero->HeroCam->Fly(3);
		break;

		// Moving down
	case GLFW_KEY_F:
		hero->HeroCam->Fly(-3);
		break;

	case GLFW_KEY_SPACE:
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
		//cout << "mouse clicked"<<endl;
        hero->Fire();
	}
}

