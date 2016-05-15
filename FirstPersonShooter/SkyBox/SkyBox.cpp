#include"SkyBox.h"
#include <glm\gtx\transform.hpp>
#include "GameComponents/StaticComponent.h"
SkyBox::SkyBox()
{ 
	Initialize();
}

SkyBox::~SkyBox()
{

}



void SkyBox::Render(ShaderProgram * Shader, mat4 VP)
{
	Shader->UseProgram();
	Shader->BindVPMatrix(&VP[0][0]);
	Shader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
	Model3D::Render(Shader,GameObject::Get_ModelMatrix(),mat4(1));
	ground->Draw();
}

void SkyBox::Initialize()
{
	
	SetModel();
	Set_Ground();
	vec3 size = vec3(50.0f,50.0f,50.0f);
	GameObject::Set_InitialTransformation(scale(size));
	GameObject::UpdateModelMatrix();

	Model3D::Set_ObjectType(ObjectType::SkyBox);
	Model3D::SetBoundingBox(Model3D::CalculateBoundingBox(Model3D::GetVertices()));
	auto boundingbox = Model3D::GetBoundingBox();
	boundingbox.Scale(size);
	boundingbox.SetCenter(GameObject::GetPosition());
	Model3D::SetBoundingBox(boundingbox);

}


void SkyBox::SetModel()
{
	if (StaticComponent::Current_Level == StaticComponent::Level1)
	{
	this->ground =  unique_ptr<TexturedModel> (new TexturedModel("data/models/skybox/negy.jpg",0));
	Model3D::LoadFromFile("data/models/skybox/Skybox.obj",true);
	}
	else if (StaticComponent::Current_Level == StaticComponent::Level2)
	{
		this->ground =  unique_ptr<TexturedModel> (new TexturedModel("data/models/skybox2/negy.jpg",0));
		Model3D::LoadFromFile("data/models/skybox2/Skybox.obj",true);
	}

	Model3D::Initialize();
}


void SkyBox::Set_Ground()
{
	float Unitsize = 100;
	ground->VertexData.push_back(vec3(Unitsize, -0, Unitsize));
	ground->VertexData.push_back(vec3(-Unitsize, -0, Unitsize));
	ground->VertexData.push_back(vec3( -Unitsize,-0 , -Unitsize));
	ground->VertexData.push_back(vec3( Unitsize, -0, -Unitsize));
	//we want a gray cube cube.
	ground->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	ground->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	ground->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	ground->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	ground->IndicesData.push_back(0);
	ground->IndicesData.push_back(1);
	ground->IndicesData.push_back(3);
	//secon.triangle.
	ground->IndicesData.push_back(1);
	ground->IndicesData.push_back(2);
	ground->IndicesData.push_back(3);

	ground->UVData.push_back(glm::vec2(0.0f, 1.0f));
	ground->UVData.push_back(glm::vec2(1.0f, 1.0f));
	ground->UVData.push_back(glm::vec2(1.0f, 0.0f));
	ground->UVData.push_back(glm::vec2(0.0f, 0.0f));

	ground->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	ground->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	ground->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	ground->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));


	ground->Initialize();
}

void SkyBox::Cleanup()
{

}

void SkyBox::Collided(ObjectType _ObjectType)
{

}
