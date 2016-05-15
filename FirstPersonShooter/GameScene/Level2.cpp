#include "Level2.h"
#include "Helper.h"
Level2::Level2() :GameScene()
{
	MapObject::Set_Model();
	Enemy::Set_EnemyModel();
	Initialize();
}


void Level2::Initialize()
{
	Initialize_Enemies();
	Initialize_MapObjects();
}

void Level2::Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{
	Render_Enemies(StaticShader,AnimationShader,VP);
	Render_MapObjects(StaticShader,VP);
}

void Level2::Update(float deltatime)
{
	Update_Enemies(deltatime);
	// vec3 dir =HelperMethods::Get_Random_Direction();
	//cout << "X :" << (float)dir.x<< " Y :" <<dir.y<<" Z :"<<dir.z << endl;
}



void Level2::Initialize_Enemies()
{

	for (int i = 0; i < 10; i++)
	{
		vec3 Random_direction = HelperMethods::Get_Random_Direction();
		cout << "X :" << (float)Random_direction.x<< " Y :" <<Random_direction.y<<" Z :"<<Random_direction.z << endl;
		Enemy* tmp_enemy= new Enemy(vec3(50,1,2),Random_direction,2,0.5f); 
		Enemies.push_back(tmp_enemy);
		StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) tmp_enemy);
	}    
}

void Level2::Update_Enemies(float deltatime)
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

void Level2::Render_Enemies(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{
	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies[i]->Render(StaticShader,AnimationShader,VP);
	}
}



void Level2::Initialize_MapObjects()
{

	float Bground = 0.5;
    float Tground = 3.0;
	float Cground = 0;

	MapObject* building1 = new MapObject(vec3(-80, Bground, 80), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building1);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building1);
	
	MapObject* building2 = new MapObject(vec3(0, Bground,80 ), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building2);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building2);

	MapObject* building3 = new MapObject(vec3(80, Bground, 80), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building3);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building3);

	MapObject* building4 = new MapObject(vec3(-40, Bground,40 ), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building4);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building4);

	MapObject* building5 = new MapObject(vec3(40, Bground, 40), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building5);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building5);

	MapObject* building6 = new MapObject(vec3(-80, Bground,0 ), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building6);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building6);

	//MapObject* building7 = new MapObject(vec3(0, Bground,0 ), vec3(-1, 0, 0), MapObject::building2);
	//MapObjects.push_back(building7);
	//StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building7);

	MapObject* building8 = new MapObject(vec3(80, Bground, 0), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building8);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building8);

	MapObject* building9 = new MapObject(vec3(-40, Bground, -40), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building9);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building9);

	MapObject* building10 = new MapObject(vec3(40, Bground,-40 ), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building10);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building10);

	MapObject* building11 = new MapObject(vec3(-80, Bground,-80 ), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building11);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building11);

	MapObject* building12 = new MapObject(vec3(0, Bground, -80), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building12);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building12);

	MapObject* building13 = new MapObject(vec3(80, Bground,-80 ), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building13);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building13);

	MapObject* building14 = new MapObject(vec3(0, Bground, -25), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building14);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building14);

	MapObject* building15 = new MapObject(vec3(0, Bground, +25), vec3(-1, 0, 0), MapObject::building2);
	MapObjects.push_back(building15);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)building15);


	//

	MapObject* tree1 = new MapObject(vec3(-40, Tground,80 ), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree1);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree1);

	MapObject* tree2 = new MapObject(vec3(40, Tground,80 ), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree2);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree2);

	MapObject* tree3 = new MapObject(vec3(-80, Tground,40 ), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree3);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree3);

	MapObject* tree4 = new MapObject(vec3(0, Tground,40 ), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree4);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree4);

	MapObject* tree5 = new MapObject(vec3(+80, Tground,40 ), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree5);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree5);

	MapObject* tree6 = new MapObject(vec3(-40, Tground,0 ), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree6);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree6);

	MapObject* tree7 = new MapObject(vec3(40, Tground, 0), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree7);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree7);

	MapObject* tree8 = new MapObject(vec3(-80, Tground,-40 ), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree8);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree8);

	MapObject* tree9 = new MapObject(vec3(0, Tground, -40), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree9);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree9);

	MapObject* tree10 = new MapObject(vec3(80, Tground, -40), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree10);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree10);

	MapObject* tree11 = new MapObject(vec3(-40, Tground, -80), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree11);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree11);

	MapObject* tree12 = new MapObject(vec3(+40, Tground, -80), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree12);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree12);

	MapObject* tree13 = new MapObject(vec3(-20, Tground, +20), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree13);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree13);

	MapObject* tree14 = new MapObject(vec3(+20, Tground, +20), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree14);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree14);

	MapObject* tree15 = new MapObject(vec3(-20, Tground, -20), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree15);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree15);

	MapObject* tree16 = new MapObject(vec3(+20, Tground, -20), vec3(-1, 0, 0), MapObject::tree);
	MapObjects.push_back(tree16);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)tree16);



	
	// Random Code
	/*
	MapObject* mapObjectsArray[35];
	int x, z,m=199,n=1,i;

	for (i = 0; i < 20; i++)
	{
		x = (rand() % m - n)-100;
		z = (rand() % m - n) - 100;
		if (x&&z == 0)x += 10;
<<<<<<< HEAD
		mapObjectsArray[i] = new MapObject(vec3(x, 1, z), vec3(-1, 0, 0), MapObject::building2);
=======
		mapObjectsArray[i] = new MapObject(vec3(x, Tground, z), vec3(-1, 0, 0), MapObject::tree);
>>>>>>> 3422f27277108d4448322ce08876ef7f46a60e25
		MapObjects.push_back(mapObjectsArray[i]);
		StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)mapObjectsArray[i]);
	}
	for (i; i < 35; i++)
	{
		x = (rand() % m - n) - 100;
		z = (rand() % m - n) - 100;
		if (x&&z == 0)x += 10;
<<<<<<< HEAD
		mapObjectsArray[i] = new MapObject(vec3(x, 1, z), vec3(-1, 0, 0), MapObject::tree);
=======
		mapObjectsArray[i] = new MapObject(vec3(x, Bground, z), vec3(-1, 0, 0), MapObject::building1);
>>>>>>> 3422f27277108d4448322ce08876ef7f46a60e25
		MapObjects.push_back(mapObjectsArray[i]);
		StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)mapObjectsArray[i]);
	}
	*/
	
}

void Level2::Update_MapObjects()
{

}

void Level2::Render_MapObjects(ShaderProgram*StaticShader,mat4 VP)
{
	for (int i = 0; i < MapObjects.size(); i++)
	{
		MapObjects[i]->Render(StaticShader,VP);
	}
}

Level2::~Level2(void)
{
}
