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

void ScreenManger::HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked)
{
	ScreenManger::Screens.top()->HandleMouse(deltaX,deltaY, LeftBtn_clicked);
}

void ScreenManger::StartScreenReturn()
{
	while (Screens.size() > 1)
	{
		delete Screens.top();
		Screens.pop();
	}
}

ScreenManger::ScreenManger(void)
{
}


ScreenManger::~ScreenManger(void)
{
}
