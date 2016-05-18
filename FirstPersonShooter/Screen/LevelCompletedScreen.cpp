#include "LevelCompletedScreen.h"


void LevelCompletedScreen::Initialize()
{
	initText2D("Holstein.DDS");
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/levelcompleted.jpg",0));

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

void LevelCompletedScreen::draw()
{
	shader.UseProgram();
	background->Draw();

}

void LevelCompletedScreen::Update(float deltaTime)
{
    float Score= (50.0f/StaticComponent::PlayingTime)*100;
	if(Score > 100) Score = 100;
	char score[100];
	itoa(Score,score,10);
	printText2D(score,530,260,60);
	printText2D("%",675,260,60);
}

void LevelCompletedScreen::close()
{
}

void LevelCompletedScreen::HandleKeyboardInput(int key)
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

LevelCompletedScreen::LevelCompletedScreen(void)
{
	this->Initialize();
}


LevelCompletedScreen::~LevelCompletedScreen(void)
{
}
