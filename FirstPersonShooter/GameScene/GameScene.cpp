#include "GameScene.h"



GameScene::GameScene()
{

}

void GameScene::Initialize(unique_ptr<CollisionManager>& collisionManager)
{

}

void GameScene::Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{

}

void GameScene::Update(unique_ptr<CollisionManager>& collisionManager,float deltatime)
{

}

void GameScene::Initialize_Enemies(unique_ptr<CollisionManager>& collisionManager)
{
	
}

void GameScene::Update_Enemies(unique_ptr<CollisionManager>& collisionManager,float deltatime)
{

}

void GameScene::Render_Enemies(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{

}

void GameScene::Initialize_MapObjects(unique_ptr<CollisionManager>& collisionManager)
{

}

void GameScene::Update_MapObjects(unique_ptr<CollisionManager>& collisionManager)
{

}

void GameScene::Render_MapObjects(ShaderProgram*StaticShader,mat4 VP)
{

}

GameScene::~GameScene(void)
{
}
