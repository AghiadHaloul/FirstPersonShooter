#include "ScreenManger.h"

stack<Screen*>ScreenManger::Screens;

void ScreenManger::AddScreen(Screen* NewScreen)
{
	ScreenManger::Screens.push(NewScreen);
}

void ScreenManger::RemoveScreen()
{ 
	delete Screens.top();
	Screens.pop();
}

void ScreenManger::Update(float deltaTime)
{
	ScreenManger::Screens.top()->Update(deltaTime);
}

void ScreenManger::Draw()
{
	ScreenManger::Screens.top()->draw();
}

void ScreenManger::HandleKeyboardInput(int key)
{
	ScreenManger::Screens.top()->HandleKeyboardInput(key);
}

void ScreenManger::HandleMouse(double deltaX,double deltaY)
{
	ScreenManger::Screens.top()->HandleMouse(deltaX,deltaY);
}

ScreenManger::ScreenManger(void)
{
}


ScreenManger::~ScreenManger(void)
{
}
