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
	if(this->GameRenderer->GameOver)
	{
		GameOverScreen *gameoversecreen = new GameOverScreen();
		ScreenManger::AddScreen(gameoversecreen);
	}
	else  if (StaticComponent::LevelCompleted)
	{
		LevelCompletedScreen *levelCompletedScreen = new LevelCompletedScreen();
		ScreenManger::AddScreen(levelCompletedScreen);
	}


}

void GameScreen::HandleKeyboardInput(int key)
{
	this->GameRenderer->HandleKeyboardInput(key);
	PauseScreen*pauseScreen;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		StaticComponent::soundEngine->StartBackMusic("music/switch.wav");
		pauseScreen = new PauseScreen();
		ScreenManger::AddScreen(pauseScreen);
		break;
	default:
		break;
	}
	
}

void GameScreen::HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked)
{
	this->GameRenderer->HandleMouse(deltaX,deltaY,LeftBtn_clicked);
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
