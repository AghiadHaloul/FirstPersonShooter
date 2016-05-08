#include "Renderer.h"
//#include "Application Manager/ApplicationManager.h"

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

	//calculate the normal of the triangle.
	shader.LoadProgram();
	animatedModelShader.LoadProgram();
/////////////////////////////////

	Game_SkyBox = unique_ptr<SkyBox> (new SkyBox(100.0f)); 
	Game_SkyBox->Initialize();

	hero = unique_ptr<Hero>(new Hero(vec3(0,-98.7,0),vec3(0,0,-1),Game_SkyBox->Unitsize));
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) hero.get());

	Firstlevel = unique_ptr<Level1>(new Level1());
	

	/////////////////////////
	
	

	//MatrixID = glGetUniformLocation(shader.programID, "MVP");
//	ModelMatrixID = glGetUniformLocation(shader.programID, "ModelMatrix");
	// Use our shader
	//glUseProgram(programID);
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
	//////////////////////////////////////////////////////////////////////////

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

void Renderer::Draw()
{		
		shader.UseProgram();

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glm::mat4 VP = hero->HeroCam->GetProjectionMatrix() * hero->HeroCam->GetViewMatrix();
		shader.BindVPMatrix(&VP[0][0]);	
		

		Game_SkyBox->Draw(shader);
        hero->Render(&shader,VP); //render nothing till now	
		Firstlevel->Render(&shader,&animatedModelShader,VP);
	    StaticComponent::sceneBullets->Render(&shader,VP);
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
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		hero->HeroCam->Fly(0.1);
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		hero->HeroCam->Fly(-0.1);
		break;
	case GLFW_KEY_RIGHT_CONTROL:
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


