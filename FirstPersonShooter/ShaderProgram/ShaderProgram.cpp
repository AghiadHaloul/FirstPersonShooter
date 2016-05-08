#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::LoadProgram()
{
	programID = LoadShaders( "SimpleTransformWithColor.vertexshader", "TextureLighting.fragmentshader");

	modelMatrixID = glGetUniformLocation(programID, "ModelMatrix");

	vpMatrixID = glGetUniformLocation(programID, "VP");


	LightPositionID = glGetUniformLocation(programID,"LightPosition_worldspace");

	AmbientLightID = glGetUniformLocation(programID,"ambientLight");
	
	EyePositionID = glGetUniformLocation(programID,"EyePosition_worldspace");
	

}

void ShaderProgram::BindModelMatrix(GLfloat* value)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void ShaderProgram::BindVPMatrix(GLfloat* value)
{
	glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}


void ShaderProgram::BindEyePosition(GLfloat* value)
{
	glUniform3fv(EyePositionID,1, value);

}


void ShaderProgram::BindAmbientLight(GLfloat* value)
{
	glUniform3fv(AmbientLightID,1, value);
}


void ShaderProgram::BindLightPosition(GLfloat* value)
{
	glUniform3fv(LightPositionID,1, value);
}

void ShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void ShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}