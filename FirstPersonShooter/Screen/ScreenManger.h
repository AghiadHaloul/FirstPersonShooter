#pragma once
#include <stack>
#include "Screen/Screen.h"
using namespace std;
class ScreenManger
{
	static stack<Screen*> Screens;
public:

	static void AddScreen(Screen* NewScreen);
	static void RemoveScreen();
	static void Update(float deltaTime);
	static void Draw();
	static void HandleKeyboardInput(int key);
	static void HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked);
	static void StartScreenReturn();
	ScreenManger(void);
	~ScreenManger(void);
};