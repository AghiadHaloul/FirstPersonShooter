#pragma once
#include "screen.h"
#include "Renderer/Renderer.h"
class GameScreen : public Screen
{
	unique_ptr<Renderer> GameRenderer;
public:
	virtual void Initialize();
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void HandleKeyboardInput(int key);
	virtual void HandleMouse(double deltaX,double deltaY);
	virtual void close();
	GameScreen(void);
	~GameScreen(void);
};

