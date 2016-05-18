#include "OptionScreen.h"


void OptionScreen::Initialize()
{
	initText2D("Holstein.DDS");
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/options.png",13));

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

}

void OptionScreen::draw()
{
	shader.UseProgram();
	background->Draw();

}

void OptionScreen::Update(float deltaTime)
{

}

void OptionScreen::close()
{

}

void OptionScreen::HandleKeyboardInput(int key)
{
	switch (key)
	{
	case GLFW_KEY_BACKSPACE:
	case GLFW_KEY_ESCAPE:
		StaticComponent::soundEngine->StartBackMusic("music/switch.wav");
		ScreenManger::RemoveScreen();
		break;
	case GLFW_KEY_LEFT:
		InputLogic();
		StaticComponent::soundEngine->StartBackMusic("music/switch.wav");
		break;
	case GLFW_KEY_RIGHT:
		InputLogic();
		StaticComponent::soundEngine->StartBackMusic("music/switch.wav");
		break;
	default:
		break;
	}
}

void OptionScreen::InputLogic()
{
	if(StaticComponent::soundEngine->On)
	{
		//printText2D("OFF",100,550,40);
		StaticComponent::soundEngine->On = false;
	}
	else
	{
		//printText2D("ON",0,300,40);
		StaticComponent::soundEngine->On = true;

	}
}


OptionScreen::OptionScreen(void)
{
	this->Initialize();
}


OptionScreen::~OptionScreen(void)
{
}
