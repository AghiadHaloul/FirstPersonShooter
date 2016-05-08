#include "OptionScreen.h"


void OptionScreen::Initialize()
{
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
	mat4 VP  = mat4(1);
	backgroundModel = mat4(1);
	shader.BindVPMatrix(&VP[0][0]);
	shader.BindModelMatrix(&backgroundModel[0][0]);
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
		ScreenManger::RemoveScreen();
		break;
	default:
		break;
	}
}

OptionScreen::OptionScreen(void)
{
	this->Initialize();
}


OptionScreen::~OptionScreen(void)
{
}
