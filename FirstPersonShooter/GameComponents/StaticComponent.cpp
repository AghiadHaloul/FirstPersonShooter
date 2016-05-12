#include "StaticComponent.h"

unique_ptr<CollisionManager>StaticComponent::collisionManager = unique_ptr<CollisionManager>(new CollisionManager());
unique_ptr<SceneBullets> StaticComponent::sceneBullets = unique_ptr<SceneBullets>(new SceneBullets());

StaticComponent::StaticComponent()
{
}

StaticComponent::~StaticComponent()
{
}

////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// SceneBullets definition 

void SceneBullets::AddBullet(Bullet* Newbullet)
{
	AllBullets.push_back(Newbullet);
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*) Newbullet);
}

void SceneBullets::Update(float deltaTime)
{
	for (int Index = 0; Index < AllBullets.size() ; Index++)
	{
		AllBullets[Index]->Update(deltaTime);

		//erasing destroyed bullet
		if(AllBullets[Index]->GetIsdestroied())
		{
			StaticComponent::collisionManager->RemoveCollidableModel((CollidableModel*)AllBullets[Index]);
			delete AllBullets[Index];//to be tested
			AllBullets.erase(AllBullets.begin()+Index);
			//cout<<"erased  bullet " << endl;
		}	
	}

}

void SceneBullets::Render(ShaderProgram*shader,mat4 VP)
{

	for (int Index = 0; Index < AllBullets.size() ; Index++)
	{
		AllBullets[Index]->Render(shader,VP);
		//cout<<"render bullet"<<endl;
	}

}

SceneBullets::SceneBullets(void)
{
}


SceneBullets::~SceneBullets(void)
{
}