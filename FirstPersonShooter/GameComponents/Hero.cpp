#include "Hero.h"

Hero::Hero():GameObject()
{
	
	GameObject::Set_InitialTransformation(glm::rotate(-90.0f,1.0f,0.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
	CMD2Model::Set_ObjectType(ObjectType::Hero);
	this->Initialize();    
	//cam initialization
	this->HeroCam = unique_ptr<EulerCamera>(new EulerCamera());
	this->HeroCam->Set_CameraBoundry(100);
	this->HeroCam->Reset(0, 0, 0,   0, 0, -1,   0, 1, 0);;
	this->HeroCam->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,4000.0f);
}


Hero::Hero(vec3 mPosition,vec3 mDirection):GameObject(mPosition,mDirection)
{
	
	GameObject::Set_InitialTransformation(glm::rotate(-90.0f,0.0f,1.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
	this->Initialize();

	//cam initialization
	this->HeroCam = unique_ptr<EulerCamera>(new EulerCamera());
	this->HeroCam->Set_CameraBoundry(100);//try to take it from sky box
	this->HeroCam->Reset(mPosition,mDirection, vec3(0,1,0));
	this->HeroCam->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,4000.0f);


}



void Hero::UpdateAnimation(float deltaTime)
{
	 CMD2Model::UpdateAnimation(&AnimationState,deltaTime);
}

void Hero::Initialize()
{
	this->step = 0.5f;

	CMD2Model::LoadModel("data/models/hero/soldier.md2");
	AnimationState = CMD2Model::StartAnimation(animType_t::STAND);
	//calculate AABBboundingbox
	this->UpdateBoundingbox();
	Bullet::Set_BulletModel();
}

void Hero::Render(ShaderProgram * shader,mat4 VP)
{ 
	
	for (int Index = 0; Index < Ammo.size() ; Index++)
	{
		Ammo[Index]->Render(shader,VP);
	}
}


void Hero::Update(unique_ptr<CollisionManager>& collisionManager,float deltaTime)
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

             cout<<"erased hero bullet " << endl;
		  }	
	}
}


void Hero::Fire(unique_ptr<CollisionManager> &collisionManager)
{
	Bullet* fired_bullet = new Bullet(HeroCam->GetEyePosition(),HeroCam->Get_mDirection(),ObjectType::HeroBullet); 
    Ammo.push_back(fired_bullet);
	collisionManager->AddCollidableModel((CollidableModel*) fired_bullet);
}

void Hero::Collided(ObjectType _ObjectType)
{
	if (_ObjectType == ObjectType::HeroBullet)
		printf("i'm your hero and i collided with hero bullet baaaaaaaaaad\n");
	else if (_ObjectType == ObjectType::Enemy)
		printf("i'm your hero and i collided with enemy \n");
}

void Hero::UpdateBoundingbox()
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
////////////////////////////////////////
void Hero::Move()
{
  GameObject::SetPosition(get_heropos());
  GameObject::SetDirection(vec3(0));

  GameObject::UpdateModelMatrix();
  
  this->UpdateBoundingbox(); //to be optimized 
  this->HeroCam->UpdateViewMatrix();
 
  
  //****************** 
  // if(CMD2Model::IsAnimationFinished)
 // AnimationState = CMD2Model::StartAnimation(animType_t::RUN);
}


void Hero::Walk_Forward()
{
   this->HeroCam->Walk(step);
   this->Move();
}

void Hero::Walk_Backward()
{
	this->HeroCam->Walk(-step);
	this->Move();
}

void Hero::Straf_Right()
{
  this->HeroCam->Strafe(step);
  this->Move();
}


void Hero::Straf_Left()
{
	this->HeroCam->Strafe(-step);
	this->Move();
}


void Hero::Yaw(double deltaX)
{
	this->HeroCam->Yaw(deltaX);
	this->HeroCam->UpdateViewMatrix();
	this->Move();
}

void Hero::Pitch(double deltaY)
{
	this->HeroCam->Pitch(deltaY);
	this->HeroCam->UpdateViewMatrix();
	this->Move();
}

vec3 Hero::get_heropos()
{
	return HeroCam->GetEyePosition()+vec3(0,-0.3,0);
}

Hero::~Hero(void)
{
}
