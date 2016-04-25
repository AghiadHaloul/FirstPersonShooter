#include"SkyBox.h"
#include <glm\gtx\transform.hpp>

SkyBox::SkyBox(GLfloat unitsize)
{

	this->Unitsize = unitsize;


	walls = new unique_ptr<TexturedModel>[6];

	//bottom - earth
	//GLfloat wall_width = 0.05;
	
	walls[0] =  unique_ptr<TexturedModel> (
		new TexturedModel("data/textures/sky/Side1.png",0)); 
	

	//front wall 
	walls[1] =  unique_ptr<TexturedModel> (
		new TexturedModel("data/textures/sky/Side2.png",1)); 
	
	// right wall
	walls[2] =  unique_ptr<TexturedModel> (
		new TexturedModel("data/textures/sky/Side3.png",2)); 
	
	// back wall
	walls[3] =  unique_ptr<TexturedModel> (
		new TexturedModel("data/textures/sky/Side4.png",3)); 

	// left wall
	walls[4] =  unique_ptr<TexturedModel> (
		new TexturedModel("data/textures/sky/Side5.png",4)); 
	// top - sky
    walls[5] =  unique_ptr<TexturedModel> (
	    new TexturedModel("data/textures/sky/Side6.png",5)); 
	
}


SkyBox::~SkyBox()
{
}


void SkyBox::Initialize()
{
	
	// bottom - floor
	walls[0]->VertexData.push_back(vec3(Unitsize, -Unitsize, Unitsize));
	walls[0]->VertexData.push_back(vec3(-Unitsize, -Unitsize, Unitsize));
	walls[0]->VertexData.push_back(vec3( -Unitsize,-Unitsize , -Unitsize));
	walls[0]->VertexData.push_back(vec3( Unitsize, -Unitsize, -Unitsize));
	//we want a gray cube cube.
	walls[0]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[0]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[0]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[0]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	walls[0]->IndicesData.push_back(0);
	walls[0]->IndicesData.push_back(1);
	walls[0]->IndicesData.push_back(3);
	//secon.triangle.
	walls[0]->IndicesData.push_back(1);
	walls[0]->IndicesData.push_back(2);
	walls[0]->IndicesData.push_back(3);
	
	walls[0]->UVData.push_back(glm::vec2(0.0f, 1.0f));
	walls[0]->UVData.push_back(glm::vec2(1.0f, 1.0f));
	walls[0]->UVData.push_back(glm::vec2(1.0f, 0.0f));
	walls[0]->UVData.push_back(glm::vec2(0.0f, 0.0f));

	walls[0]->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	walls[0]->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	walls[0]->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	walls[0]->NormalsData.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	
	walls[0]->Initialize();
	
	//front
	walls[1]->VertexData.push_back(vec3(-Unitsize, -Unitsize, Unitsize));
	walls[1]->VertexData.push_back(vec3(Unitsize, -Unitsize, Unitsize));
	walls[1]->VertexData.push_back(vec3( Unitsize,  Unitsize, Unitsize));
	walls[1]->VertexData.push_back(vec3( -Unitsize,  Unitsize, Unitsize));
	//we want a gray cube cube.
	walls[1]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[1]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[1]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[1]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	walls[1]->IndicesData.push_back(0);
	walls[1]->IndicesData.push_back(1);
	walls[1]->IndicesData.push_back(3);
	//secon.triangle.
	walls[1]->IndicesData.push_back(1);
	walls[1]->IndicesData.push_back(2);
	walls[1]->IndicesData.push_back(3);
	
	walls[1]->UVData.push_back(glm::vec2(0.0f, 1.0f));
	walls[1]->UVData.push_back(glm::vec2(1.0f, 1.0f));
	walls[1]->UVData.push_back(glm::vec2(1.0f, 0.0f));
	walls[1]->UVData.push_back(glm::vec2(0.0f, 0.0f));

	walls[1]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	walls[1]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	walls[1]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	walls[1]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

	walls[1]->Initialize();

	// right
	walls[2]->VertexData.push_back(vec3(Unitsize, -Unitsize, Unitsize));
	walls[2]->VertexData.push_back(vec3(Unitsize, -Unitsize, -Unitsize));
	walls[2]->VertexData.push_back(vec3( Unitsize,  Unitsize, -Unitsize));
	walls[2]->VertexData.push_back(vec3( Unitsize,  Unitsize, Unitsize));
	//we want a gray cube cube.
	walls[2]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[2]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[2]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[2]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	walls[2]->IndicesData.push_back(0);
	walls[2]->IndicesData.push_back(1);
	walls[2]->IndicesData.push_back(3);
	//secon.triangle.
	walls[2]->IndicesData.push_back(1);
	walls[2]->IndicesData.push_back(2);
	walls[2]->IndicesData.push_back(3);
	
	walls[2]->UVData.push_back(glm::vec2(0.0f, 1.0f));
	walls[2]->UVData.push_back(glm::vec2(1.0f, 1.0f));
	walls[2]->UVData.push_back(glm::vec2(1.0f, 0.0f));
	walls[2]->UVData.push_back(glm::vec2(0.0f, 0.0f));

	walls[2]->NormalsData.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	walls[2]->NormalsData.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	walls[2]->NormalsData.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	walls[2]->NormalsData.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));

	
	walls[2]->Initialize();


	//back

	walls[3]->VertexData.push_back(vec3(Unitsize, -Unitsize, -Unitsize));
	walls[3]->VertexData.push_back(vec3(-Unitsize, -Unitsize, -Unitsize));
	walls[3]->VertexData.push_back(vec3( -Unitsize,  Unitsize,-Unitsize));
	walls[3]->VertexData.push_back(vec3( Unitsize,  Unitsize, -Unitsize));
	//we want a gray cube cube.
	walls[3]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[3]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[3]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[3]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	walls[3]->IndicesData.push_back(0);
	walls[3]->IndicesData.push_back(1);
	walls[3]->IndicesData.push_back(3);
	//secon.triangle.
	walls[3]->IndicesData.push_back(1);
	walls[3]->IndicesData.push_back(2);
	walls[3]->IndicesData.push_back(3);
	
	walls[3]->UVData.push_back(glm::vec2(0.0f, 1.0f));
	walls[3]->UVData.push_back(glm::vec2(1.0f, 1.0f));
	walls[3]->UVData.push_back(glm::vec2(1.0f, 0.0f));
	walls[3]->UVData.push_back(glm::vec2(0.0f, 0.0f));

	walls[3]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	walls[3]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	walls[3]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	walls[3]->NormalsData.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	walls[3]->Initialize();
	
	//left
	walls[4]->VertexData.push_back(vec3(-Unitsize, -Unitsize, -Unitsize));
	walls[4]->VertexData.push_back(vec3(-Unitsize, -Unitsize, Unitsize));
	walls[4]->VertexData.push_back(vec3( -Unitsize,  Unitsize, Unitsize));
	walls[4]->VertexData.push_back(vec3( -Unitsize,  Unitsize, -Unitsize));
	//we want a gray cube cube.
	walls[4]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[4]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[4]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[4]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	walls[4]->IndicesData.push_back(0);
	walls[4]->IndicesData.push_back(1);
	walls[4]->IndicesData.push_back(3);
	//secon.triangle.
	walls[4]->IndicesData.push_back(1);
	walls[4]->IndicesData.push_back(2);
	walls[4]->IndicesData.push_back(3);
	
	walls[4]->UVData.push_back(glm::vec2(0.0f, 1.0f));
	walls[4]->UVData.push_back(glm::vec2(1.0f, 1.0f));
	walls[4]->UVData.push_back(glm::vec2(1.0f, 0.0f));
	walls[4]->UVData.push_back(glm::vec2(0.0f, 0.0f));

	walls[4]->NormalsData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	walls[4]->NormalsData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	walls[4]->NormalsData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	walls[4]->NormalsData.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	walls[4]->Initialize();

	//top
	walls[5]->VertexData.push_back(vec3(-Unitsize, Unitsize, Unitsize));
	walls[5]->VertexData.push_back(vec3(Unitsize, Unitsize, Unitsize));
	walls[5]->VertexData.push_back(vec3( Unitsize,  Unitsize, -Unitsize));
	walls[5]->VertexData.push_back(vec3( -Unitsize,  Unitsize, -Unitsize));
	//we want a gray cube cube.
	walls[5]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[5]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[5]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	walls[5]->ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	walls[5]->IndicesData.push_back(0);
	walls[5]->IndicesData.push_back(1);
	walls[5]->IndicesData.push_back(3);
	//secon.triangle.
	walls[5]->IndicesData.push_back(1);
	walls[5]->IndicesData.push_back(2);
	walls[5]->IndicesData.push_back(3);
	
	walls[5]->UVData.push_back(glm::vec2(0.0f, 1.0f));
	walls[5]->UVData.push_back(glm::vec2(1.0f, 1.0f));
	walls[5]->UVData.push_back(glm::vec2(1.0f, 0.0f));
	walls[5]->UVData.push_back(glm::vec2(0.0f, 0.0f));

	walls[5]->NormalsData.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	walls[5]->NormalsData.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	walls[5]->NormalsData.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	walls[5]->NormalsData.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	
	walls[5]->Initialize();
	

}


void SkyBox::Draw(ShaderProgram &shader)
{
	//mSquare->texture->Bind();
	mat4 I = mat4();//glm::rotate(90.f,vec3(0.0,0.0,1.0));
	shader.BindModelMatrix(&I[0][0]);
	//mSquare->Draw();
	
	for (int i = 0; i < 6; i++)
	{
		walls[i]->Draw();
	}
}