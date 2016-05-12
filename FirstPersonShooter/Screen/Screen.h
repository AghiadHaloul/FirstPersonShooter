#pragma once
class Screen
{
public:
	virtual void Initialize()=0;
	virtual void draw();
	virtual void Update(float deltaTime);
	virtual void close();
	virtual void HandleKeyboardInput(int key);
	virtual void HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked);
	Screen(void);
	~Screen(void);
};

