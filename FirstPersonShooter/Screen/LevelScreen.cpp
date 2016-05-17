#include "LevelScreen.h"

LevelScreen::LevelScreen(void)
{
	Initialize();
}


void LevelScreen::Initialize()
{
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/level/level1.jpg",0));

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

	this->Choice = LevelScreenchoice::level1;
}

void LevelScreen::draw()	
{
	shader.UseProgram();
	background->Draw();
}

void LevelScreen::Update(float deltaTime)
{
	
}

void LevelScreen::HandleKeyboardInput(int key)
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
	case GLFW_KEY_BACKSPACE:
		ScreenManger::RemoveScreen();
		break;
		
	default:
		break;

	}

	//applicationmanager::keypressed = -1;
}

void LevelScreen::handel_UPkey()
{
	switch (Choice)
	{
	case LevelScreenchoice::level1:
		Choice = LevelScreenchoice::level2;
		background->texture = new Texture("data/textures/menu/level/level2.jpg",13);
		break;
	case LevelScreenchoice::level2:
		Choice = LevelScreenchoice::level1;
		background->texture = new Texture("data/textures/menu/level/level1.jpg",13);
		break;

   default:
		break;
	}
}


void LevelScreen::handel_Downkey()
{
	switch (Choice)
	{
	case LevelScreenchoice::level1:
		Choice = LevelScreenchoice::level2;
		background->texture = new Texture("data/textures/menu/level/level2.jpg",13);
		break;
	case LevelScreenchoice::level2:
		Choice = LevelScreenchoice::level1;
		background->texture = new Texture("data/textures/menu/level/level1.jpg",13);
		break;

	default:
		break;
	}
}

void LevelScreen::handel_Enterkey()
{
	switch (Choice)
	{
	case LevelScreenchoice::level1:
		StaticComponent::Current_Level = StaticComponent::GameLevel::Level1;
		break;
	case LevelScreenchoice::level2:
		StaticComponent::Current_Level = StaticComponent::GameLevel::Level2;
		break;
	default:
		break;
	}
	LoadingScreen* loadingScreen = new LoadingScreen();
	ScreenManger::AddScreen(loadingScreen);

}

void LevelScreen::HandleMouse(double deltaX,double deltaY, bool LeftBtn_clicked)
{

}

void LevelScreen::close()
{

}

LevelScreen::~LevelScreen(void)
{
}
