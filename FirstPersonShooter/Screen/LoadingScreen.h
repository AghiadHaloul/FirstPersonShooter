#pragma once
#include "screen.h"
#include <glm/glm.hpp>
#include "Model/TexturedModel.h"
#include <memory>
#include "StartScreen.h"
#include "GameScreen.h"
using namespace glm;
class LoadingScreen :
	public Screen
{
	SimpleShaderProgram shader;
	unique_ptr<TexturedModel> background;
	mat4 backgroundModel;
	float loadtimer;
public:
	virtual void Initialize();
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void close();
	LoadingScreen(void);
	~LoadingScreen(void);
};

