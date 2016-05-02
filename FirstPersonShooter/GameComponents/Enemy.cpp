#include "Enemy.h"



Enemy::Enemy(vec3 mPosition,vec3 mDirection):GameObject(mPosition,mDirection)
{
	GameObject::Set_InitialTransformation(glm::rotate(-90.0f,1.0f,0.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
	CMD2Model::Set_ObjectType(ObjectType::Enemy);
	Initialize();
}


void Enemy::UpdateBoundingbox()
{
	CMD2Model::SetBoundingBox(CollidableModel::CalculateBoundingBox(CMD2Model::GetVertices()));
	auto tmpboundingbox = CMD2Model::GetBoundingBox();
	tmpboundingbox.Scale(0.01f,0.01f,0.01f);
	tmpboundingbox.Rotate(-90.0f,1.0f,0.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::Get_XZ_DirectionAngle(),0.0f,1.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::Get_YZ_DirectionAngle(),1.0f,0.0f,0.0f);
	tmpboundingbox.Translate(GameObject::GetPosition());
	CMD2Model::SetBoundingBox(tmpboundingbox);
}

void Enemy::Initialize()
{
	//this->step = 0.5f;
	CMD2Model::LoadModel("data/models/enemy/robot.md2");
	AnimationState = CMD2Model::StartAnimation(animType_t::STAND);
	 GameObject::UpdateModelMatrix();
	this->UpdateBoundingbox();
}

void Enemy::Render(KeyFrameAnimationShader *shader,mat4 VP)
{
	if(!GameObject::GetIsdestroied())
	{
	shader->UseProgram();
	shader->BindVPMatrix(&VP[0][0]);
	shader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
	CMD2Model::RenderModel(&AnimationState,shader);
	}
}


void Enemy::UpdateAnimation(float deltaTime)
{
	 CMD2Model::UpdateAnimation(&AnimationState,deltaTime);
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

Enemy::~Enemy(void)
{
}
