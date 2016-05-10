#pragma once
#include "screen.h"
#include <glm/glm.hpp>
#include "Model/TexturedModel.h"
#include <memory>
#include "ShaderProgram/SimpleShaderProgram.h"
#include "Application Manager/ApplicationManager.h"
#include "LoadingScreen.h"
#include "OptionScreen.h"
#include "CreditsScreen.h"

//#include "LoadingScreen.h"
using namespace std;
using namespace glm;
class StartScreen : public Screen
{
public:
	enum StartScreenchoice{PlayGame,Options,Credits,Quit,Nochoice};
private:
	StartScreenchoice Choice;
	SimpleShaderProgram shader;
	unique_ptr<TexturedModel> background;

	void handel_UPkey();
	void handel_Downkey();
	void handel_Enterkey();
public:
	StartScreen(void);
	virtual void Initialize();
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void HandleKeyboardInput(int key);
	virtual void HandleMouse(double deltaX,double deltaY);
	virtual void close();
	~StartScreen(void);
};

