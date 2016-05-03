#include "Renderer.h"



Renderer::Renderer()
{
    
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

	collisionManager = std::unique_ptr<CollisionManager>( new CollisionManager());
	Game_SkyBox = unique_ptr<SkyBox> (new SkyBox(100.0f)); 
	Game_SkyBox->Initialize();


	hero = unique_ptr<Hero>(new Hero(vec3(0,-98.7,0),vec3(0,0,-1)));
	collisionManager->AddCollidableModel((CollidableModel*) hero.get());

	Firstlevel = unique_ptr<Level1>(new Level1(collisionManager));
	

	/////////////////////////
	
	

	//MatrixID = glGetUniformLocation(shader.programID, "MVP");
	ModelMatrixID = glGetUniformLocation(shader.programID, "ModelMatrix");
	// Use our shader
	//glUseProgram(programID);
	shader.UseProgram();
	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	LightPositionID = glGetUniformLocation(shader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(0,0,0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(shader.programID,"ambientLight");
	ambientLight = glm::vec3(0.1,0.1,0.1);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(shader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID,1, &hero->HeroCam->GetEyePosition()[0]);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	animatedModelShader.UseProgram();
	LightPositionID = glGetUniformLocation(animatedModelShader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(1.0,0.25,0.0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(animatedModelShader.programID,"ambientLight");
	ambientLight = glm::vec3(0.5,0.5,0.5);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID,1, &hero->HeroCam->GetEyePosition()[0]);



}

void Renderer::Draw()
{		
		shader.UseProgram();

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glm::mat4 VP = hero->HeroCam->GetProjectionMatrix() * hero->HeroCam->GetViewMatrix();
		shader.BindVPMatrix(&VP[0][0]);	
		Game_SkyBox->Draw(shader);
        hero->Render(&shader,VP);	
		Firstlevel->Render(&shader,&animatedModelShader,VP);
	

}

void Renderer::Cleanup()
{
    glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{
	collisionManager->UpdateCollisions();
	hero->Update(collisionManager,deltaTime/1000);
	Firstlevel->Update(collisionManager,deltaTime/1000);

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
	case GLFW_KEY_B:
		hero->Fire(collisionManager);
		break;

	default:
		break;
	}

	//update the eye position uniform.
	glUniform3fv(EyePositionID,1, &hero->HeroCam->GetEyePosition()[0]);

}

void Renderer::HandleMouse(double deltaX,double deltaY)
{	
	hero->Yaw(deltaX);
	hero->Pitch(deltaY);
	//update the eye position uniform.
	glUniform3fv(EyePositionID,1, &hero->HeroCam->GetEyePosition()[0]);
}


