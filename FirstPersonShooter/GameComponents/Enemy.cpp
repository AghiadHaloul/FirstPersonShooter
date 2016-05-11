#include "Enemy.h"
#include "Helper.h"


Enemy::Enemy(vec3 mPosition,vec3 mDirection):GameObject(mPosition,mDirection)
{
	Initialize();
	enemySensor=unique_ptr<Sensor>(new Sensor(&(GameObject::Position),&(GameObject::Direction),&FireEnable,&isMoving));
	StaticComponent::collisionManager->AddCollidableModel((CollidableModel*)enemySensor.get());
}



void Enemy::Initialize()
{
	this->Speed = 5.0f;
	this->MaxDist = 50;
	this->Distance = 0;
	this->isMoving = true;
	this->FireEnable = false;
	this->isdead = false;
	this->fireholdTime = 0;
	this->deathTime = 0;
	GameObject::Set_InitialTransformation(glm::rotate(-90.0f,1.0f,0.0f,0.0f) * glm::scale(0.05f,0.05f,0.05f));
	CollidableModel::Set_ObjectType(ObjectType::Enemy);
	AnimationState = EnemyModel.StartAnimation(animType_t::RUN);
	GameObject::UpdateModelMatrix();
	this->InitializeBoundingbox();
}

void Enemy::InitializeBoundingbox()
{
	CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(EnemyModel.GetVertices()));
	auto tmpboundingbox = CollidableModel::GetBoundingBox();
	tmpboundingbox.Scale(0.05f,0.05f,0.05f);
	tmpboundingbox.Rotate(-90.0f,1.0f,0.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::Get_XZ_DirectionAngle(),0.0f,1.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::Get_YZ_DirectionAngle(),1.0f,0.0f,0.0f);
	tmpboundingbox.Translate(GameObject::GetPosition());
	CollidableModel::SetBoundingBox(tmpboundingbox);
}

void Enemy::UpdateBoundingbox()
{
	auto tmpboundingbox = CollidableModel::GetBoundingBox();
	tmpboundingbox.SetCenter(GameObject::GetPosition());
	CollidableModel::SetBoundingBox(tmpboundingbox);
	enemySensor->Update_BoundingBox();
}

void Enemy::Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP)
{

	AnimationShader->UseProgram();
	AnimationShader->BindVPMatrix(&VP[0][0]);
	AnimationShader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
	EnemyModel.RenderModel(&AnimationState,AnimationShader);

}


void Enemy::Update(float deltaTime)
{
	UpdateAnimation(deltaTime);
	if(!isdead)
	{
		if(isMoving)
		{
			Move(deltaTime);
			if(AnimationState.type != animType_t::RUN)
				AnimationState = EnemyModel.StartAnimation(animType_t::RUN);
		}
		else
		{
			if(AnimationState.type != animType_t::ATTACK)
				AnimationState = EnemyModel.StartAnimation(animType_t::ATTACK);
		}

		if(FireEnable)
		{
			Fire();
			FireEnable=false;
		}
	}
	else
	{
     Update_Death(deltaTime);
	}
	
	fireholdTime+=deltaTime;
	isMoving = true;
	GameObject::UpdateModelMatrix();
	this->UpdateBoundingbox();
}

void Enemy::Update_Death(float deltaTime)
{ 
	    deathTime+=deltaTime;
		if(AnimationState.type != animType_t::DEATH_FALLBACK)
		AnimationState = EnemyModel.StartAnimation(animType_t::DEATH_FALLBACK);
		//GameObject::Set_InitialTransformation(glm::rotate(-90.0f,0.0f,1.0f,0.0f) * glm::scale(0.05f,0.05f,0.05f));
	    if(deathTime > 0.80)
			{
				GameObject::SetIsdestroied(true); 
		        StaticComponent::collisionManager->RemoveCollidableModel((CollidableModel*)enemySensor.get());
		    }
}

void Enemy::UpdateAnimation(float deltaTime)
{
	EnemyModel.UpdateAnimation(&AnimationState,deltaTime);
}

void Enemy::Move(float deltaTime)
{
	float step = Speed*deltaTime;
	vec3 newpos = GameObject::GetPosition()+GameObject::GetDirection()*step; 
	GameObject::SetPosition(newpos);
	Distance += step;
	if (Distance >= MaxDist )
	{
		GameObject::SetDirection(HelperMethods::Get_Random_Direction());
		Distance = 0;
	}
	if (stupid_bounding())
	{
		GameObject::SetDirection(-GetDirection());
		Distance = 0;
	}

}

void Enemy::Fire()
{

	if(fireholdTime > 0.5)
	{
		Bullet* fired_bullet = new Bullet(GameObject::GetPosition(),GameObject::GetDirection(),ObjectType::EnemyBullet); 
		StaticComponent::sceneBullets->AddBullet(fired_bullet);
		fireholdTime = 0;
	}
}

void Enemy::Collided(ObjectType _ObjectType)
{
	if (_ObjectType == ObjectType::MapObject)
	{
		vec3 newpos = GameObject::GetPosition()+(-GameObject::GetDirection()); 
		GameObject::SetPosition(newpos);
		GameObject::SetDirection(-GameObject::GetDirection());
	}
	else if (_ObjectType == ObjectType::HeroBullet)
	{
		printf("i'm your enemy and i collided with hero bullet and i'm gonna disappeare but still here don't for get me  \n");
		this->isdead = true;
		this->deathTime = 0;
	}
	
}


void Enemy::Set_EnemyModel()
{
	Sensor::Set_Model();
	EnemyModel.LoadModel("data/models/enemy/robot.md2");
}
CMD2Model Enemy::EnemyModel;
Enemy::~Enemy(void)
{

}
