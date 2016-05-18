#ifndef GraphicsDevice_h__
#define GraphicsDevice_h__

#include <gl/glew.h>
#include "Shaders/shader.hpp"
#include <string>
#include <glm\glm.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace glm;
class ShaderProgram
{
#define  maxlights 4
	public:
	GLuint programID;

	GLuint modelMatrixID;
	GLuint vpMatrixID;

	GLuint AmbientLightID;
	GLuint LightPositionID[maxlights];
	GLuint LightcolorID[maxlights];

	GLuint EyePositionID;

	ShaderProgram();
	~ShaderProgram();

	void BindModelMatrix(GLfloat* value);
	void BindVPMatrix(GLfloat* value);
	
	void BindEyePosition(GLfloat* value);
	void BindAmbientLight(GLfloat* value);
	void BindLightPositions(vector<vec3>lightPostions);
	void BindLightColors(vector<vec3> lightColors);

	//calls glUseProgram.
	void UseProgram();
	//load shaders from files.
	virtual void LoadProgram();
	void CleanUp();
};

#endif // GraphicsDevice_h__