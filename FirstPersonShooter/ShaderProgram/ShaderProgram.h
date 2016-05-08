#ifndef GraphicsDevice_h__
#define GraphicsDevice_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"


class ShaderProgram
{
	public:
	GLuint programID;

	GLuint modelMatrixID;
	GLuint vpMatrixID;

	GLuint AmbientLightID;
	GLuint LightPositionID;
	GLuint EyePositionID;

	ShaderProgram();
	~ShaderProgram();

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

#endif // GraphicsDevice_h__