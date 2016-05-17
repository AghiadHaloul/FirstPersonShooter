#pragma once
#include "screen.h"
#include <glm/glm.hpp>
#include "Model/TexturedModel.h"
#include <memory>
#include "Screen/StartScreen.h"
using namespace glm;
class LevelCompletedScreen :
	public Screen
{
	SimpleShaderProgram shader;
	unique_ptr<TexturedModel> background;
	
public:
	virtual void Initialize();
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void close();
	virtual void HandleKeyboardInput(int key);
	LevelCompletedScreen(void);
	~LevelCompletedScreen(void);
};

