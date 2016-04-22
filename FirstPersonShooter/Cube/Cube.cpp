#include "Cube.h"

#include <glm\gtx\transform.hpp>


Cube::Cube(string TexturePath,int TextUnit,vec3 Translate, vec3 Scale)
{
	mSquare = new TexturedModel();
	mSquare->texture = new Texture(TexturePath, TextUnit);
    
	CubeModelMatrix = scale(Scale)*translate(Translate);
}


Cube::~Cube(void)
{
}

void Cube::Initialize()
{

	mSquare->VertexData.push_back(vec3(-1.0f, -1.0f, 0.0f));
	mSquare->VertexData.push_back(vec3(1.0f, -1.0f, 0.0f));
	mSquare->VertexData.push_back(vec3( 1.0f,  1.0f, 0.0f));
	mSquare->VertexData.push_back(vec3( -1.0f,  1.0f, 0.0f));
	//we want a gray cube cube.
	mSquare->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	mSquare->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	mSquare->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	mSquare->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	mSquare->IndicesData.push_back(0);
	mSquare->IndicesData.push_back(1);
	mSquare->IndicesData.push_back(3);
	//secon.triangle.
	mSquare->IndicesData.push_back(1);
	mSquare->IndicesData.push_back(2);
	mSquare->IndicesData.push_back(3);
	
	mSquare->UVData.push_back(glm::vec2(0.0f, 0.0f));
	mSquare->UVData.push_back(glm::vec2(1.0f, 0.0f));
	mSquare->UVData.push_back(glm::vec2(1.0f, 1.0f));
	mSquare->UVData.push_back(glm::vec2(0.0f, 1.0f));

	mSquare->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	mSquare->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	mSquare->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	mSquare->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));


	
	mSquare->Initialize();



	int numberOfFaces = 6;
	mFacesModelMatrices.resize(numberOfFaces);
	
	//bottom
	mFacesModelMatrices[0] = glm::translate(0.0f,-1.0f,0.0f)*glm::rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
	//top
	mFacesModelMatrices[1] = glm::translate(0.0f,1.0f,0.0f)*glm::rotate(-90.0f,glm::vec3(1.0f,0.0f,0.0f));
	//front
	mFacesModelMatrices[2] = glm::translate(0.0f,0.0f,1.0f);
	//back
	mFacesModelMatrices[3] = glm::translate(0.0f,0.0f,-1.0f)*glm::rotate(180.0f,glm::vec3(1.0f,0.0f,0.0f));
	//left
	mFacesModelMatrices[4] = glm::translate(-1.0f,0.0f,0.0f)*glm::rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	//right
    mFacesModelMatrices[5] = glm::translate(1.0f,0.0f,0.0f)*glm::rotate(90.0f,glm::vec3(0.0f,1.0f,0.0f));
	
	//this transformation is applied on the whole cube!!!
	
}

void Cube::Draw(ShaderProgram &shader)
{
	mSquare->texture->Bind();
	for (int i = 0; i < mFacesModelMatrices.size(); i++)
	{
		glm::mat4 model = CubeModelMatrix * mFacesModelMatrices[i];
		shader.BindModelMatrix(&model[0][0]);
		//shader.BindVPMatrix(&VP[0][0]);
		mSquare->Draw();
	}
}
