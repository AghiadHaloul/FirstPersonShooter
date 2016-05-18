#include "KeyFrameAnimationShader.h"


KeyFrameAnimationShader::KeyFrameAnimationShader(void)
{
}


KeyFrameAnimationShader::~KeyFrameAnimationShader(void)
{
}

void KeyFrameAnimationShader::LoadProgram()
{
	programID = LoadShaders( "KeyframeAnimation.vertexshader", "TextureLighting.fragmentshader");

	modelMatrixID = glGetUniformLocation(programID, "ModelMatrix");

	vpMatrixID = glGetUniformLocation(programID, "VP");

	interpolationID = glGetUniformLocation(programID, "Interpolation");

	for (int i = 0; i < maxlights; i++)
	{
		string s = to_string(i);
		string lightref =  "LightPosition_worldspace["+s+"]";
		string colorref =  "LightColor["+s+"]";
		cout <<  colorref <<endl; cout <<  lightref <<endl;
		LightPositionID[i] = glGetUniformLocation(programID,lightref.c_str());
		LightcolorID[i] = glGetUniformLocation(programID,colorref.c_str()) ;
	}
	AmbientLightID = glGetUniformLocation(programID,"ambientLight");

	EyePositionID = glGetUniformLocation(programID,"EyePosition_worldspace");
}

void KeyFrameAnimationShader::SetInterpolation(float interpolation)
{
	glUniform1f(interpolationID,interpolation);
}
