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
	myCamera = std::unique_ptr<EulerCamera>(new EulerCamera());
	//calculate the normal of the triangle.


	//since the triangle is not connected to anything else, so the normal is constant on all the vertices.

	//drawing a square.


	//first triangle.
	
	//second triangle.
	
	SkyBox = unique_ptr<Cube> (new Cube("data/textures/bricks.jpg",1,vec3(0,-10,-1),vec3(20,0.5,20))); 
	SkyBox->Initialize();
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////

	

	//////////////////////////////////////////////////////////////////////////
	//Load model from OBJ file.

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//load model.

	//read model and it's textures from HDD.

	//send the meshes to the GPU.


	

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
	lightPosition = glm::vec3(1,1,1);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(shader.programID,"ambientLight");
	ambientLight = glm::vec3(0.1,0.1,0.1);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(shader.programID,"EyePosition_worldspace");
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);

	// View matrix : 
	myCamera->Reset(0.0,1.0,5.0 ,0,0,0, 0,1,0);	
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
	//////////////////////////////////////////////////////////////////////////

}

void Renderer::Draw()
{		
		shader.UseProgram();

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
		shader.BindVPMatrix(&VP[0][0]);

		SkyBox->Draw(shader);
		//1st triangle

		/*glm::mat4 triangle1MVP =   VP * triangle1M; 
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle1MVP[0][0]);*/

		//we need to send the model matrix to transform the normals too.
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &triangle1M[0][0]);
		//the floor
		//we need to send the model matrix to transform the normals too.
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);
		

	

		////////////////////////////////////////////////////////////////////////////
		////Draw the cube.
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &myCube->CubeModelMatrix[0][0]);
		//myCube->Draw(MatrixID,VP);
		////////////////////////////////////////////////////////////////////////////
}

void Renderer::Cleanup()
{
    glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{

}

void Renderer::HandleKeyboardInput(int key)
{
	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		myCamera->Walk(1.0);
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		myCamera->Walk(-1.0);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		myCamera->Strafe(1.0);
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		myCamera->Strafe(-1.0);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		myCamera->Fly(1.0);
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		myCamera->Fly(-1.0);
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

