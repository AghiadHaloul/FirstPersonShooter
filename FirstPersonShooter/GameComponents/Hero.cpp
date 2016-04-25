#include "Hero.h"

Hero::Hero(KeyFrameAnimationShader *mshader):GameObject()
{
	this->shader = mshader;
	this->Initialize();
}


Hero::Hero(KeyFrameAnimationShader *mshader,vec3 mPosition,vec3 mDirection,bool misdestroied ):GameObject(mPosition,mDirection,misdestroied)
{
	this->shader = mshader;
	this->Initialize();

}


void Hero::UpdateAnimation(float deltaTime)
{
	 CMD2Model::UpdateAnimation(&AnimationState,deltaTime);
}

void Hero::Initialize()
{
	CMD2Model::LoadModel("data/models/hero/soldier.md2");
	AnimationState = CMD2Model::StartAnimation(animType_t::RUN);
	//calculate AABBboundingbox
	this->UpdateBoundingbox();

}

void Hero::Render(mat4 VP)
{ 
	this->shader->UseProgram();
	this->shader->BindVPMatrix(&VP[0][0]);
	this->shader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
	CMD2Model::RenderModel(&AnimationState,this->shader);
}

void Hero::Collided(ObjectType _ObjectType)
{
	printf("IAM THE HERO 3AAAAAAAAAAAA\n");
}

void Hero::Move(vec3 NewDirection)
{
  float step = 0.05f;
  GameObject::SetDirection(NewDirection);
  vec3 NewPosition = GameObject::GetPosition()+NewDirection*step;
  GameObject::SetPosition(NewPosition);
  GameObject::UpdateModelMatrix();
  this->UpdateBoundingbox();
 // if(CMD2Model::IsAnimationFinished)
 // AnimationState = CMD2Model::StartAnimation(animType_t::RUN);


}

void Hero::UpdateBoundingbox()
{

	CMD2Model::SetBoundingBox(CollidableModel::CalculateBoundingBox(CMD2Model::GetVertices()));
	auto tmpboundingbox = CMD2Model::GetBoundingBox();
	tmpboundingbox.Scale(0.01f,0.01f,0.01f);
	tmpboundingbox.Rotate(-90.0f,1.0f,0.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::GetDirectionAngle(),1.0f,0.0f,0.0f);
	tmpboundingbox.Translate(GameObject::GetPosition());
	CMD2Model::SetBoundingBox(tmpboundingbox);


}
Hero::~Hero(void)
{
}
