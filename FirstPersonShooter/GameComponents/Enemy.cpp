#include "Enemy.h"



Enemy::Enemy(vec3 mPosition,vec3 mDirection):GameObject(mPosition,mDirection)
{
	
	Initialize();
}



void Enemy::Initialize()
{
	//this->step = 0.5f;
	GameObject::Set_InitialTransformation(glm::rotate(-90.0f,1.0f,0.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
	CollidableModel::Set_ObjectType(ObjectType::Enemy);
	AnimationState = EnemyModel.StartAnimation(animType_t::STAND);
	GameObject::UpdateModelMatrix();
	this->UpdateBoundingbox();
}

void Enemy::UpdateBoundingbox()
{
	CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(EnemyModel.GetVertices()));
	auto tmpboundingbox = CollidableModel::GetBoundingBox();
	tmpboundingbox.Scale(0.01f,0.01f,0.01f);
	tmpboundingbox.Rotate(-90.0f,1.0f,0.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::Get_XZ_DirectionAngle(),0.0f,1.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::Get_YZ_DirectionAngle(),1.0f,0.0f,0.0f);
	tmpboundingbox.Translate(GameObject::GetPosition());
	CollidableModel::SetBoundingBox(tmpboundingbox);
}

void Enemy::Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{

		AnimationShader->UseProgram();
		AnimationShader->BindVPMatrix(&VP[0][0]);
		AnimationShader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
		EnemyModel.RenderModel(&AnimationState,AnimationShader);


	for (int Index = 0; Index < Ammo.size() ; Index++)
	{
		Ammo[Index]->Render(StaticShader,VP);
	}

}


void Enemy::UpdateAnimation(float deltaTime)
{
	 EnemyModel.UpdateAnimation(&AnimationState,deltaTime);
}

void Enemy::Collided(ObjectType _ObjectType)
{
	if (_ObjectType == ObjectType::HeroBullet)
	{
	 printf("i'm your enemy and i collided with hero bullet and i'm gonna disappeare but still here don't for get me  \n");
	 GameObject::SetIsdestroied(true);
	}
	else if (_ObjectType == ObjectType::Hero)
	printf("i'm your enemy and i collided with hero  \n");

}

void Enemy::Fire(unique_ptr<CollisionManager>& collisionManager)
{
	Bullet* fired_bullet = new Bullet(GameObject::GetPosition(),GameObject::GetDirection(),ObjectType::EnemyBullet); 
	Ammo.push_back(fired_bullet);
	collisionManager->AddCollidableModel((CollidableModel*) fired_bullet);
}

void Enemy::Update(unique_ptr<CollisionManager>&collisionManager,float deltaTime)
{
	for (int Index = 0; Index < Ammo.size() ; Index++)
	{
		Ammo[Index]->Update(deltaTime);

		//erasing destroyed bullet
		if(Ammo[Index]->GetIsdestroied())
		{
			collisionManager->RemoveCollidableModel((CollidableModel*)Ammo[Index]);
			delete Ammo[Index];//to be tested
			Ammo.erase(Ammo.begin()+Index);

			cout<<"erased enemy bullet " << endl;
		}	
	}
}

void Enemy::Set_EnemyModel()
{
	EnemyModel.LoadModel("data/models/enemy/robot.md2");
	
}
CMD2Model Enemy::EnemyModel;
Enemy::~Enemy(void)
{

}
