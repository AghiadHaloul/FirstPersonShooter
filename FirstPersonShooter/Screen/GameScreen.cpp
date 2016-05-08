#include "GameScreen.h"
void GameScreen::Initialize()
{
	this->GameRenderer = unique_ptr<Renderer>(new Renderer());
}

void GameScreen::draw()
{
	this->GameRenderer->Draw();
}

void GameScreen::Update(float deltaTime)
{
	this->GameRenderer->Update(deltaTime);
}

void GameScreen::HandleKeyboardInput(int key)
{
	this->GameRenderer->HandleKeyboardInput(key);
	switch (key)
	{
	
	default:
		break;
	}
	
}

void GameScreen::HandleMouse(double deltaX,double deltaY)
{
	this->GameRenderer->HandleMouse(deltaX,deltaY);
}

void GameScreen::close()
{
	this->GameRenderer->Cleanup();
}

GameScreen::GameScreen(void)
{
	this->Initialize();
}

GameScreen::~GameScreen(void)
{
	this->close();
}
