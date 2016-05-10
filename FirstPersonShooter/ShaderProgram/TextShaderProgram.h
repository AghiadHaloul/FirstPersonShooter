
#include <gl/glew.h>
#include "Shaders/shader.hpp"

class TextShaderProgram
{
	public:
	GLuint programID;

	GLuint modelMatrixID;
	GLuint vpMatrixID;


	TextShaderProgram();
	~TextShaderProgram();

	void BindModelMatrix(GLfloat* value);
	void BindVPMatrix(GLfloat* value);
	
	void BindEyePosition(GLfloat* value);
	void BindAmbientLight(GLfloat* value);
	void BindLightPosition(GLfloat* value);

	//calls glUseProgram.
	void UseProgram();
	//load shaders from files.
	virtual void LoadProgram();
	void CleanUp();
};

