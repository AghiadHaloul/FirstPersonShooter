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
		vec3 Random_direction = HelperMethods::Get_Random_Direction();
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
	MapObject* tree1= new MapObject(vec3(-2,-99.9,2),vec3(-1,0,0),MapObject::tree); 
	MapObjects.push_back(tree1);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) tree1);

	MapObject* building1= new MapObject(vec3(-20,-99.9,8),vec3(-1,0,0),MapObject::building1); 
	MapObjects.push_back(building1);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) building1);	

	MapObject* building2= new MapObject(vec3(-40,-99.9,-40),vec3(-1,0,0),MapObject::building1); 
	MapObjects.push_back(building2);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) building2);	

	MapObject* tree2= new MapObject(vec3(-2,-99.9,-30),vec3(-1,0,0),MapObject::tree); 
	MapObjects.push_back(tree2);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) tree2);	

	MapObject* building3= new MapObject(vec3(-26,-99.9,18),vec3(-1,0,0),MapObject::building1); 
	MapObjects.push_back(building3);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) building3);	

	MapObject* tree3= new MapObject(vec3(-32,-99.9,-30),vec3(-1,0,0),MapObject::tree); 
	MapObjects.push_back(tree3);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) tree3);	
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
