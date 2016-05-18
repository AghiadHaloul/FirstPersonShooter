#include "GameOverScreen.h"


void GameOverScreen::Initialize()
{
	initText2D("Holstein.DDS");
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/gameover.png",0));

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

void GameOverScreen::draw()
{
	shader.UseProgram();
	background->Draw();

}

void GameOverScreen::Update(float deltaTime)
{
}

void GameOverScreen::close()
{
}

void GameOverScreen::HandleKeyboardInput(int key)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
	StaticComponent::soundEngine->StartBackMusic("music/switch.wav");
		ScreenManger::StartScreenReturn();
		break;
	default:
		break;
	}
}

GameOverScreen::GameOverScreen(void)
{
	this->Initialize();
}


GameOverScreen::~GameOverScreen(void)
{
}
