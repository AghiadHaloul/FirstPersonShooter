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

}

void SimpleShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void SimpleShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}