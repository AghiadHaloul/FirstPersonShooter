#include "LoadingScreen.h"


void LoadingScreen::Initialize()
{
	background = unique_ptr<TexturedModel>(new TexturedModel("data/textures/menu/loading.jpg",13));

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
	loadtimer = 0;
}

void LoadingScreen::draw()
{
	shader.UseProgram();
	background->Draw();

}

void LoadingScreen::Update(float deltaTime)
{
	loadtimer+=deltaTime;
	if(loadtimer>500)
	{
		GameScreen* gameScreen= new GameScreen();
		ScreenManger::AddScreen(gameScreen);
	}

}

void LoadingScreen::close()
{

}

LoadingScreen::LoadingScreen(void)
{
	Initialize();
}


LoadingScreen::~LoadingScreen(void)
{
}
