#include"SkyBox.h"

SkyBox::SkyBox(GLint unitsize)
{
	walls = new unique_ptr<Cube>[6];
	//bottom - earth
	GLfloat wall_width = 0.05;
	walls[0] =  unique_ptr<Cube> (
		new Cube("data/textures/sky/Side1.png",0,vec3(0,-unitsize/2,0),vec3(unitsize,wall_width,unitsize))); 
	// top - sky
	walls[1] =  unique_ptr<Cube> (
		new Cube("data/textures/sky/Side6.png",1,vec3(0,unitsize/2,0),vec3(unitsize,wall_width,unitsize))); 
	//front wall 
	walls[2] =  unique_ptr<Cube> (
		new Cube("data/textures/sky/Side2.png",2,vec3(0,0,unitsize/2),vec3(unitsize,unitsize,wall_width))); 
	// back wall
	walls[3] =  unique_ptr<Cube> (
		new Cube("data/textures/sky/Side4.png",3,vec3(0,0,-unitsize/2),vec3(unitsize,unitsize,wall_width))); 
	// wall
	walls[4] =  unique_ptr<Cube> (
		new Cube("data/textures/sky/Side3.png",4,vec3(unitsize/2,0,0),vec3(wall_width,unitsize,unitsize))); 
	// wall
	walls[5] =  unique_ptr<Cube> (
		new Cube("data/textures/sky/Side5.png",5,vec3(-unitsize/2,0,0),vec3(wall_width,unitsize,unitsize))); 

}

SkyBox::~SkyBox()
{
}

void SkyBox::Initialize()
{
  	for (int i = 0; i < 6; i++)
	{
		walls[i]->Initialize();
	}	
}

void SkyBox::Draw(ShaderProgram &shader)
{
	for (int i = 0; i < 6; i++)
	{
		walls[i]->Draw(shader);
	}
}