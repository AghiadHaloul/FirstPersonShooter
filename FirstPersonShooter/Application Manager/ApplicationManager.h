#ifndef ApplicationManager_h__
#define ApplicationManager_h__
#include <Windows.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <memory>
#include "Screen/ScreenManger.h"
#include "Screen/StartScreen.h"

class ApplicationManager
{

	int mOpenGLMajorVersion;
	int mOpenGLMinorVersion;
	double mTime;

	GLFWwindow* mWindow; //Why didn't we use smart pointers here? google it! ;)
//	std::unique_ptr<Renderer> mRenderer;

	void InitializeComponents();
	void HandleKeyboardInput();
	void HandleMouseLocation();
	void Update();
	static void SpecialKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseMoved(GLFWwindow* window, double xpos, double ypos);
	static void WindowResized(GLFWwindow* window, int width, int height);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static int WindowSizeWidth; 
	static int WindowSizeHeight;
	static bool LeftBtn_clicked;
public:
	static bool exitLoop;
	static int KeyPressed; //Keep the code of the pressed key
	
	static double movedDistanceX;
	static double movedDistanceY;
	static double MouseXPos; //Keep the x-value of the mouse position
	static double MouseYPos; //Keep the y-value of the mouse position

	ApplicationManager(int pOpenGLMajorVersion, int pOpenGLMinorVersion);

	bool InitalizeApplication(int pWindowSizeWidth, int pWindowSizeHeight);
	void StartMainLoop();
	void CloseApplication();

	~ApplicationManager(void);
};
#endif // ApplicationManager_h__

