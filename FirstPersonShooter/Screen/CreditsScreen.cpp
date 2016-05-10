#include "CreditsScreen.h"



void CreditsScreen::Initialize()
{
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/credits.jpg",13));

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

void CreditsScreen::draw()
{
	shader.UseProgram();
	background->Draw();

}

void CreditsScreen::Update(float deltaTime)
{
}

void CreditsScreen::close()
{
}

void CreditsScreen::HandleKeyboardInput(int key)
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

CreditsScreen::CreditsScreen(void)
{
	this->Initialize();
}


CreditsScreen::~CreditsScreen(void)
{
}
