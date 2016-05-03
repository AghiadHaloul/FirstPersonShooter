#include "Level1.h"


Level1::Level1(unique_ptr<CollisionManager>& collisionManager):GameScene()
{
	MapObject::Set_Model();
	Initialize(collisionManager);
}


void Level1::Initialize(unique_ptr<CollisionManager>& collisionManager)
{
	Initialize_Enemies(collisionManager);
	Initialize_MapObjects(collisionManager);
}

void Level1::Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{
  Render_Enemies(StaticShader,AnimationShader,VP);
  Render_MapObjects(StaticShader,VP);
}

void Level1::Update(unique_ptr<CollisionManager>& collisionManager,float deltatime)
{
  Update_Enemies(collisionManager,deltatime);
}



void Level1::Initialize_Enemies(unique_ptr<CollisionManager>& collisionManager)
{
	for (int i = 0; i < 1; i++)
	{
		Enemy* tmp_enemy= new Enemy(vec3(-3,-99,0),vec3(-1,0,0)); 
        Enemies.push_back(tmp_enemy);
		collisionManager->AddCollidableModel((CollidableModel*) tmp_enemy);
	}
}

void Level1::Update_Enemies(unique_ptr<CollisionManager>& collisionManager,float deltatime)
{
	for (int Index = 0; Index < GameScene::Enemies.size() ; Index++)
	{
		Enemies[Index]->Update(collisionManager,deltatime);

		//erasing destroyed enemy
		if(Enemies[Index]->GetIsdestroied())
		{
			collisionManager->RemoveCollidableModel((CollidableModel*)Enemies[Index]);
			delete Enemies[Index];//to be tested
			Enemies.erase(Enemies.begin()+Index);

			cout<<"erased Enemy " << endl;
		}	
	}
}

void Level1::Render_Enemies(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{
	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies[i]->Render(StaticShader,AnimationShader,VP);
	}
}



void Level1::Initialize_MapObjects(unique_ptr<CollisionManager>& collisionManager)
{
	for (int i = 0; i < 1; i++)
	{
		MapObject* tmp_mapObject= new MapObject(vec3(-2,-99,0),vec3(-1,0,0)); 
		MapObjects.push_back(tmp_mapObject);
		collisionManager->AddCollidableModel((CollidableModel*) tmp_mapObject);
	}
}

void Level1::Update_MapObjects(unique_ptr<CollisionManager>& collisionManager)
{

}

void Level1::Render_MapObjects(ShaderProgram*StaticShader,mat4 VP)
{
	for (int i = 0; i < MapObjects.size(); i++)
	{
		MapObjects[i]->Render(StaticShader,VP);
	}
}

Level1::~Level1(void)
{
}
