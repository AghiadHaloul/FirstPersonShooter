#include "TextShaderProgram.h"

TextShaderProgram::TextShaderProgram()
{
}

TextShaderProgram::~TextShaderProgram()
{
}

void TextShaderProgram::LoadProgram()
{
	programID = LoadShaders( "TextVertexShader.vertexshader", "TextVertexShader.fragmentshader");

	modelMatrixID = glGetUniformLocation(programID, "ModelMatrix");

	vpMatrixID = glGetUniformLocation(programID, "VP");	

}

void TextShaderProgram::BindModelMatrix(GLfloat* value)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void TextShaderProgram::BindVPMatrix(GLfloat* value)
{
	glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}


void TextShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void TextShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}