#pragma once
#include "screen.h"
#include <glm/glm.hpp>
#include "Model/TexturedModel.h"
#include <memory>
#include "Screen/StartScreen.h"
using namespace glm;
class OptionScreen :
	public Screen
{	
	
SimpleShaderProgram shader;
unique_ptr<TexturedModel> background;
mat4 backgroundModel;

public:
	virtual void Initialize();
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void close();
	virtual void HandleKeyboardInput(int key);
	OptionScreen(void);
	~OptionScreen(void);
};

