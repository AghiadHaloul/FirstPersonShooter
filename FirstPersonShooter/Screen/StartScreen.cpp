#include "StartScreen.h"

StartScreen::StartScreen(void)
{
	Initialize();
}


void StartScreen::Initialize()
{
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/mainmenu/default.jpg",13));

	background->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	background->VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	background->VertexData.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
	background->VertexData.push_back(glm::vec3( -1.0f,  1.0f, 0.0f));
	
	background->UVData.push_back(glm::vec2(0.0f,1.0f));
	background->UVData.push_back(glm::vec2(1.0f,1.0f));
	background->UVData.push_back(glm::vec2(1.0f,0.0f));
	background->UVData.push_back(glm::vec2(0.0f,0.0f));

	//first triangle.
	background->IndicesData.push_back(0);
	background->IndicesData.push_back(1);
	background->IndicesData.push_back(3);
	//second triangle.
	background->IndicesData.push_back(1);
	background->IndicesData.push_back(2);
	background->IndicesData.push_back(3);
	background->Initialize();
	
	
	shader.LoadProgram();

	Choice = StartScreenChoice::NoChoice;
}

void StartScreen::draw()	
{
	shader.UseProgram();
	background->Draw();
}

void StartScreen::Update(float deltaTime)
{
	
}

void StartScreen::HandleKeyboardInput(int key)
{
	
	switch (key)
	{
	case GLFW_KEY_UP:
		handel_UPkey();
		break;

	case GLFW_KEY_DOWN:
		handel_Downkey();
		break;
	case GLFW_KEY_ENTER:
		handel_Enterkey();
		break;

	default:
		break;
	}

	//ApplicationManager::KeyPressed = -1;
}

void StartScreen::handel_UPkey()
{
	switch (Choice)
	{
	case StartScreen::PlayGame:
		Choice = StartScreenChoice::Quit;
		background->texture = new Texture("data/textures/menu/mainmenu/quit.jpg",13);
		break;
	case StartScreen::Options:
		Choice = StartScreenChoice::PlayGame;
		background->texture = new Texture("data/textures/menu/mainmenu/playgame.jpg",13);
		break;
	case StartScreen::Credits:
		Choice = StartScreenChoice::Options;
		background->texture = new Texture("data/textures/menu/mainmenu/options.jpg",13);
		break;
	case StartScreen::Quit:
		Choice = StartScreenChoice::Credits;
		background->texture = new Texture("data/textures/menu/mainmenu/credits.jpg",13);
		break;
	case StartScreen::NoChoice:
		Choice = StartScreenChoice::Quit;
		background->texture = new Texture("data/textures/menu/mainmenu/quit.jpg",13);
		break;
	default:
		break;
	}
}


void StartScreen::handel_Downkey()
{
	switch (Choice)
	{
	case StartScreen::PlayGame:
		Choice = StartScreenChoice::Options;
		background->texture = new Texture("data/textures/menu/mainmenu/options.jpg",13);
		break;
	case StartScreen::Options:
		Choice = StartScreenChoice::Credits;
		background->texture = new Texture("data/textures/menu/mainmenu/credits.jpg",13);
		break;
	case StartScreen::Credits:
		Choice = StartScreenChoice::Quit;
		background->texture = new Texture("data/textures/menu/mainmenu/quit.jpg",13);
		break;
	case StartScreen::Quit:
		Choice = StartScreenChoice::PlayGame;
		background->texture = new Texture("data/textures/menu/mainmenu/playgame.jpg",13);
		break;
	case StartScreen::NoChoice:
		Choice = StartScreenChoice::PlayGame;
		background->texture = new Texture("data/textures/menu/mainmenu/playgame.jpg",13);
		break;
	default:
		break;
	}
}

void StartScreen::handel_Enterkey()
{
	LoadingScreen *loadingScreen;
	CreditsScreen *creditsScreen;
	OptionScreen * optionscreen;
	switch (Choice)
	{
	case StartScreen::PlayGame:
		loadingScreen = new LoadingScreen();
		ScreenManger::AddScreen(loadingScreen);
		break;
	case StartScreen::Options:
		optionscreen = new OptionScreen();
		ScreenManger::AddScreen(optionscreen);
		break;
	case StartScreen::Credits:
		creditsScreen = new CreditsScreen();
		ScreenManger::AddScreen(creditsScreen);
		break;
	case StartScreen::Quit:
		ApplicationManager::exitLoop = true;
		break;
	case StartScreen::NoChoice:
		break;
	default:
		break;
	}
}

void StartScreen::HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked)
{

}

void StartScreen::close()
{

}

StartScreen::~StartScreen(void)
{
}
