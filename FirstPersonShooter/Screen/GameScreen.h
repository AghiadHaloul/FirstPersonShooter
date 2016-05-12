#pragma once
#include "screen.h"
#include "Renderer/Renderer.h"
#include "Screen/StartScreen.h"
#include "GameOverScreen.h"
#include "text2D.hpp"
#include "PauseScreen.h"
class GameScreen : public Screen
{
	unique_ptr<Renderer> GameRenderer;
public:
	virtual void Initialize();
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void HandleKeyboardInput(int key);
	virtual void HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked);
	virtual void close();
	GameScreen(void);
	~GameScreen(void);
};

