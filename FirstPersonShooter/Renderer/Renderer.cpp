#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include "OBJLoader/objloader.hpp"


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
	collisionManager = std::unique_ptr<CollisionManager>( new CollisionManager());
	shader.LoadProgram();
	animatedModelShader.LoadProgram();
	//since the triangle is not connected to anything else, so the normal is constant on all the vertices.

	//drawing a square.


	//first triangle.
	
	//second triangle.
	
	Game_SkyBox = unique_ptr<SkyBox> (new SkyBox(100.0f)); 
	Game_SkyBox->Initialize();

	myCamera = std::unique_ptr<EulerCamera>(new EulerCamera());
	myCamera->Set_CameraBoundry(Game_SkyBox->Unitsize);
	//////////////////////////////////////////////////////////////////////////
	hero = unique_ptr<Hero>(new Hero(&animatedModelShader));
	collisionManager->AddCollidableModel((CollidableModel*) hero.get());


	//////////////////////////////////////////////////////////////////////////
	//Load model from OBJ file.
	/*
	house = std::unique_ptr<Model3D>(new Model3D());
	house->LoadFromFile("data/models/House/house.3ds");
	house->Initialize();
	house->SetBoundingBox(CollidableModel::CalculateBoundingBox(house->GetVertices(),-2.0f));
	collisionManager->AddCollidableModel((CollidableModel*) house.get());
	
	houseM = glm::rotate(90.0f,1.0f,0.0f,0.0f) *glm::scale(0.1f,0.1f,0.1f);
	auto tempBox = house->GetBoundingBox();
	tempBox.Scale(0.1f,0.1f,0.1f);
	tempBox.Rotate(90.0f,1.0f,0.0f,0.0f);
	house->SetBoundingBox(tempBox);
	*/
	//**********************************************
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//load model.

	//read model and it's textures from HDD.

	//send the meshes to the GPU.


	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,4000.0f);
	// View matrix : 
	myCamera->Reset(0,2,2 ,0,0,0, 0,1,0);	
	//send the eye position to the shaders.
	
	//////////////////////////////////////////////////////////////////////////

	// Create and compile our GLSL program from the shaders
	//programID = LoadShaders( "SimpleTransformWithColor.vertexshader", "MultiColor.fragmentshader" );
	shader.LoadProgram();
	
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
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	animatedModelShader.LoadProgram();
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
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
}

void Renderer::Draw()
{		
		shader.UseProgram();

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
		shader.BindVPMatrix(&VP[0][0]);
	
		Game_SkyBox->Draw(shader);
		//house->Render(&shader,houseM);
		
		hero->Render(VP);
	//	mat4 modelmat = translate(vec3(0,-2,-1))*scale(vec3(0.05,0.05,0.05))*rotate(90.f,vec3(1,0,0));
		//shader.BindModelMatrix(&modelmat[0][0]);
	//	soldier->Render(&shader,modelmat);
		/*
		animatedModelShader.UseProgram();
		animatedModelShader.BindVPMatrix(&VP[0][0]);
		animatedModelShader.BindModelMatrix(&bladeM[0][0]);
		blade.RenderModel(&bladeAnimationState,&animatedModelShader);
		*/

}

void Renderer::Cleanup()
{
    glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{
	
	hero->UpdateAnimation(deltaTime/1000);
	//blade.UpdateAnimation(&bladeAnimationState,deltaTime/1000);
	collisionManager->UpdateCollisions();
}

void Renderer::HandleKeyboardInput(int key)
{
	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
		hero->Move(vec3(0,0,-1));
		break;

	case GLFW_KEY_W:
		myCamera->Walk(1);
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
		hero->Move(vec3(0,0,1));
		break;
	case GLFW_KEY_S:
		myCamera->Walk(-1);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
		hero->Move(vec3(1,0,0));
		break;
	case GLFW_KEY_D:
		myCamera->Strafe(1);
		break;

		// Moving left
	case GLFW_KEY_LEFT:
		hero->Move(vec3(-1,0,0));
		break;
	case GLFW_KEY_A:
		myCamera->Strafe(-1);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		myCamera->Fly(1);
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		myCamera->Fly(-1);
		break;
	default:
		break;
	}


	//continue the remaining movements.

	myCamera->UpdateViewMatrix();

	//update the eye position uniform.
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);

}

void Renderer::HandleMouse(double deltaX,double deltaY)
{	
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();
	//update the eye position uniform.
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
}

