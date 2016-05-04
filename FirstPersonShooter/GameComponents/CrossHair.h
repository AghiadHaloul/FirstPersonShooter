#pragma once
#include "GameComponents\gameobject.h"
#include "Model\TexturedModel.h"
#include "OBJLoader\objloader.hpp"
class CrossHair : public GameObject
{
	TexturedModel*CrossHairModel;
public:

	CrossHair(vec3 mpostion);
	void Initialize();
	void Render(ShaderProgram* StaticShader,mat4 VP);
	void Move(vec3 mpostion,vec3 Direction);
	~CrossHair(void);
};

