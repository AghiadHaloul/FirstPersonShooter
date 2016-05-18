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

	for (int i = 0; i < maxlights; i++)
	{
	 string s = to_string(i);
	 string lightref =  "LightPosition_worldspace["+s+"]";
	 string colorref =  "LightColor["+s+"]";
	
	 cout <<  colorref <<endl;
	 cout <<  lightref <<endl;
	 LightPositionID[i] = glGetUniformLocation(programID,lightref.c_str());
	 LightcolorID[i] = glGetUniformLocation(programID,colorref.c_str()) ;
	}
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




void ShaderProgram::BindLightPositions(vector<vec3>lightPostions)
{
	for (int i = 0; i < maxlights; i++)
	{
		glUniform3fv(LightPositionID[i],1, &lightPostions[i][0]);
	}
}


void ShaderProgram::BindLightColors(vector<vec3> lightColors)
{
	for (int i = 0; i < maxlights; i++)
	{
		glUniform3fv(LightcolorID[i],1, &lightColors[i][0]);
	}
}

void ShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void ShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}