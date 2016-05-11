#include "PauseScreen.h"

PauseScreen::PauseScreen(void)
{
	Initialize();
}


void PauseScreen::Initialize()
{
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/pause/continue.jpg",0));

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

	this->Choice = PauseScreenchoice::Continue;
}

void PauseScreen::draw()	
{
	shader.UseProgram();
	background->Draw();
}

void PauseScreen::Update(float deltaTime)
{
	
}

void PauseScreen::HandleKeyboardInput(int key)
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
	case GLFW_KEY_ESCAPE:
		ScreenManger::RemoveScreen();
		break;
		
	default:
		break;

	}

	//applicationmanager::keypressed = -1;
}

void PauseScreen::handel_UPkey()
{
	switch (Choice)
	{
	case PauseScreenchoice::Continue:
		Choice = PauseScreenchoice::Exit;
		background->texture = new Texture("data/textures/menu/pause/exit.jpg",13);
		break;
	case PauseScreenchoice::Options:
		Choice = PauseScreenchoice::Continue;
		background->texture = new Texture("data/textures/menu/pause/continue.jpg",13);
		break;
	case PauseScreenchoice::Exit:
		Choice = PauseScreenchoice::Options;
		background->texture = new Texture("data/textures/menu/pause/options.jpg",13);
		break;
   default:
		break;
	}
}


void PauseScreen::handel_Downkey()
{
	switch (Choice)
	{
	case PauseScreenchoice::Continue:
		Choice = PauseScreenchoice::Options;
		background->texture = new Texture("data/textures/menu/pause/options.jpg",13);
		break;
	case PauseScreenchoice::Options:
		Choice = PauseScreenchoice::Exit;
		background->texture = new Texture("data/textures/menu/pause/exit.jpg",13);
		break;
	case PauseScreenchoice::Exit:
		Choice = PauseScreenchoice::Continue;
		background->texture = new Texture("data/textures/menu/pause/continue.jpg",13);
		break;

	default:
		break;
	}
}

void PauseScreen::handel_Enterkey()
{
	OptionScreen * optionscreen;
	switch (Choice)
	{
	case PauseScreenchoice::Continue:
		ScreenManger::RemoveScreen();
		break;
	case PauseScreenchoice::Options:
		optionscreen = new OptionScreen();
		ScreenManger::AddScreen(optionscreen);
		break;
	case PauseScreenchoice::Exit:
		ScreenManger::StartScreenReturn();
		break;
	default:
		break;
	}
}

void PauseScreen::HandleMouse(double deltax,double deltay)
{

}

void PauseScreen::close()
{

}

PauseScreen::~PauseScreen(void)
{
}
