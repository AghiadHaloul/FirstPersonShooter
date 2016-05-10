
#include <gl/glew.h>
#include "Shaders/shader.hpp"

class SimpleShaderProgram
{
	public:
	GLuint programID;

	


	SimpleShaderProgram();
	~SimpleShaderProgram();


	//calls glUseProgram.
	void UseProgram();
	//load shaders from files.
	virtual void LoadProgram();
	void CleanUp();
};

