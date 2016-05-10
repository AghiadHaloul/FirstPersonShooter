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
	initText2D("Holstein.DDS");

	//calculate the normal of the triangle.
	shader.LoadProgram();
	animatedModelShader.LoadProgram();
	simpleshader.LoadProgram();
/////////////////////////////////

	Game_SkyBox = unique_ptr<SkyBox> (new SkyBox(100.0f)); 
	Game_SkyBox->Initialize();

	hero = unique_ptr<Hero>(new Hero(vec3(0,-98.7,0),vec3(0,0,-1),Game_SkyBox->Unitsize));
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) hero.get());

	Firstlevel = unique_ptr<Level1>(new Level1());
	

	shader.UseProgram();
	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	lightPosition = glm::vec3(-50,-50,-50);
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


	///cross hair
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/cross.png",27));

	background->VertexData.push_back(glm::vec3(-0.1f, -0.1f, 0.0f));
	background->VertexData.push_back(glm::vec3(0.1f ,-0.1f ,0.0f));
	background->VertexData.push_back(glm::vec3( 0.1f ,0.1f, 0.0f));
	background->VertexData.push_back(glm::vec3( -0.1f , 0.1f, 0.0f));

	background->UVData.push_back(glm::vec2(0.0f,1.0f));
	background->UVData.push_back(glm::vec2(1.0f,1.0f));
	background->UVData.push_back(glm::vec2(1.0f,0.0f));
	background->UVData.push_back(glm::vec2(0.0f,0.0f));

	//first triangle.
	background->IndicesData.push_back(0);
	background->IndicesData.push_back(1);
	background->IndicesData.push_back(3);
	//second triangle.
	background->IndicesData.push_back(1);
	background->IndicesData.push_back(2);
	background->IndicesData.push_back(3);
	background->Initialize();
 

	fix_Error2();
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


		
		simpleshader.UseProgram();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		background->Draw();
		glDisable(GL_BLEND);
	
		DrawText();
}


void Renderer::DrawText()
{
	fix_Error();
	printText2D("my name islam",0,0,60);
	printText2D("allah yaslam",0,200,60);

}
void Renderer::fix_Error()
{
	shader.UseProgram();
    background2->Draw();
}


void Renderer::fix_Error2()
{
	background2 = unique_ptr<TexturedModel>(new TexturedModel("data/textures/cross.png",27));

	background2->VertexData.push_back(glm::vec3(-0.1f, -0.1f, 0.0f));
	background2->VertexData.push_back(glm::vec3(0.1f ,-0.1f ,0.0f));
	background2->VertexData.push_back(glm::vec3( 0.1f ,0.1f, 0.0f));

	background2->UVData.push_back(glm::vec2(0.0f,1.0f));
	background2->UVData.push_back(glm::vec2(1.0f,1.0f));
	background2->UVData.push_back(glm::vec2(1.0f,0.0f));

	//first triangle.
	background2->Initialize();
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
		hero->HeroCam->Fly(0.1);
		break;

		// Moving down
	case GLFW_KEY_F:
		hero->HeroCam->Fly(-0.1);
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

void Renderer::HandleMouse(double deltaX,double deltaY)
{	
	hero->Yaw(deltaX);
	hero->Pitch(deltaY);
	//update the eye position uniform.
	shader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);
	animatedModelShader.BindEyePosition(&hero->HeroCam->GetEyePosition()[0]);
}

