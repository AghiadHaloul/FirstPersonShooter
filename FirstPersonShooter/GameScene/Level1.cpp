#include "Level1.h"
#include "Helper.h"
Level1::Level1() :GameScene()
{
	MapObject::Set_Model();
	Enemy::Set_EnemyModel();
	Initialize();
}


void Level1::Initialize()
{
	Initialize_Enemies();
	Initialize_MapObjects();
}

void Level1::Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{
  Render_Enemies(StaticShader,AnimationShader,VP);
  Render_MapObjects(StaticShader,VP);
}

void Level1::Update(float deltatime)
{
  Update_Enemies(deltatime);
 // vec3 dir =HelperMethods::Get_Random_Direction();
  //cout << "X :" << (float)dir.x<< " Y :" <<dir.y<<" Z :"<<dir.z << endl;
}



void Level1::Initialize_Enemies()
{
	
	for (int i = 0; i < 10; i++)
	{
		vec3 Random_direction =HelperMethods::Get_Random_Direction();
		cout << "X :" << (float)Random_direction.x<< " Y :" <<Random_direction.y<<" Z :"<<Random_direction.z << endl;
		Enemy* tmp_enemy= new Enemy(vec3(50,-99,2),Random_direction); 
        Enemies.push_back(tmp_enemy);
		StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) tmp_enemy);
	}    
}

void Level1::Update_Enemies(float deltatime)
{
	for (int Index = 0; Index < GameScene::Enemies.size() ; Index++)
	{
		Enemies[Index]->Update(deltatime);

		//erasing destroyed enemy
		if(Enemies[Index]->GetIsdestroied())
		{
			StaticComponent::collisionManager->RemoveCollidableModel((CollidableModel*)Enemies[Index]);
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



void Level1::Initialize_MapObjects()
{
	for (int i = 0; i < 0; i++)
	{
		MapObject* tmp_mapObject= new MapObject(vec3(-2,-99,0),vec3(-1,0,0)); 
		MapObjects.push_back(tmp_mapObject);
		StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) tmp_mapObject);
	}
}

void Level1::Update_MapObjects()
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
