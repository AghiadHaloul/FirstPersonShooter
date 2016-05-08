#include "SimpleShaderProgram.h"

SimpleShaderProgram::SimpleShaderProgram()
{
}

SimpleShaderProgram::~SimpleShaderProgram()
{
}

void SimpleShaderProgram::LoadProgram()
{
	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleTextureShader.fragmentshader");

	modelMatrixID = glGetUniformLocation(programID, "ModelMatrix");

	vpMatrixID = glGetUniformLocation(programID, "VP");	

}

void SimpleShaderProgram::BindModelMatrix(GLfloat* value)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void SimpleShaderProgram::BindVPMatrix(GLfloat* value)
{
	glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}


void SimpleShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void SimpleShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}