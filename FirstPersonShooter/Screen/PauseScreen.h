#pragma once
#include "screen.h"
#include <glm/glm.hpp>
#include "Model/TexturedModel.h"
#include <memory>
#include "OptionScreen.h"

//#include "LoadingScreen.h"
using namespace std;
using namespace glm;
class PauseScreen : public Screen
{
public:
	enum PauseScreenchoice{Continue,Options,Exit};
private:
	PauseScreenchoice Choice;
	SimpleShaderProgram shader;
	unique_ptr<TexturedModel> background;

	void handel_UPkey();
	void handel_Downkey();
	void handel_Enterkey();
public:
	PauseScreen(void);
	virtual void Initialize();
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void HandleKeyboardInput(int key);
	virtual void HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked);
	virtual void close();
	~PauseScreen(void);
};

