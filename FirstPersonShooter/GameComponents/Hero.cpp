#include "Hero.h"
#include "CollisionDetection/sensor.h"
Hero::Hero():GameObject()
{
	
	GameObject::Set_InitialTransformation(glm::rotate(-90.0f,1.0f,0.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
	CMD2Model::Set_ObjectType(ObjectType::Hero); 
	//cam initialization
	this->HeroCam = unique_ptr<EulerCamera>(new EulerCamera());
	this->HeroCam->Set_CameraBoundry(100);
	this->HeroCam->Reset(0, 0, 0,   0, 0, -1,   0, 1, 0);;
	this->HeroCam->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,4000.0f);
 //   HeroCross = new CrossHair(HeroCam->GetEyePosition());
}


Hero::Hero(vec3 mPosition,vec3 mDirection,float boundry):GameObject(mPosition,mDirection)
{
	
	GameObject::Set_InitialTransformation(glm::rotate(-90.0f,0.0f,1.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
	this->Initialize();
	CMD2Model::Set_ObjectType(ObjectType::Hero); 
	//cam initialization
	this->HeroCam = unique_ptr<EulerCamera>(new EulerCamera());
	this->HeroCam->Set_CameraBoundry(boundry);//try to take it from sky box
	this->HeroCam->Reset(mPosition,mDirection, vec3(0,1,0));
	this->HeroCam->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,4000.0f);
	//under testing 
//	HeroCross = new CrossHair(mPosition+mDirection);
}



void Hero::UpdateAnimation(float deltaTime)
{
	 CMD2Model::UpdateAnimation(&AnimationState,deltaTime);
}

void Hero::Initialize()
{
	this->step = 0.6f;
	this->health = HeroHealth;
	CMD2Model::LoadModel("data/models/hero/soldier.md2");
	AnimationState = CMD2Model::StartAnimation(animType_t::STAND);
	//calculate AABBboundingbox
	this->UpdateBoundingbox();
	Bullet::Set_BulletModel();
	//firehold = 0;
}

void Hero::Render(ShaderProgram * shader,mat4 VP)
{ 
	//under testing
//	HeroCross->Render(shader,VP);
}


void Hero::Update(float deltaTime)
{
	cout << "X " << GameObject::GetPosition().x<< " Z " << GameObject::GetPosition().z <<endl;
	//firehold+=deltaTime;
}


void Hero::Fire()
{
	Bullet* fired_bullet = new Bullet(HeroCam->GetEyePosition(),HeroCam->Get_mDirection(),ObjectType::HeroBullet); 
    StaticComponent::sceneBullets->AddBullet(fired_bullet);
	
	//if(firehold > 0.25)	{ firehold = 0;} if there is fire hold
}


void Hero::UpdateBoundingbox()
{

	CMD2Model::SetBoundingBox(CollidableModel::CalculateBoundingBox(CMD2Model::GetVertices()));
	auto tmpboundingbox = CMD2Model::GetBoundingBox();
	tmpboundingbox.Scale(0.01f,0.01f,0.01f);
	tmpboundingbox.Rotate(-90.0f,1.0f,0.0f,0.0f);
	tmpboundingbox.Rotate(GameObject::Get_XZ_DirectionAngle(),0.0f,1.0f,0.0f);
	tmpboundingbox.Translate(GameObject::GetPosition());
	CMD2Model::SetBoundingBox(tmpboundingbox);
}
////////////////////////////////////////
void Hero::Move()
{
  GameObject::SetPosition(get_heropos());
  GameObject::SetDirection(HeroCam->Get_mDirection());
  Sensor::HeroPostion = vec3(get_heropos().x,0,get_heropos().z); //sensor(enemy) must be aware of hero direction
  GameObject::UpdateModelMatrix();
  this->UpdateBoundingbox(); //to be optimized 
  this->HeroCam->UpdateViewMatrix();
 
  //under testing 
 //HeroCross->Move(HeroCam->GetEyePosition()+HeroCam->Get_mDirection());
  
  //****************** 
  // if(CMD2Model::IsAnimationFinished)
 // AnimationState = CMD2Model::StartAnimation(animType_t::RUN);
}


void Hero::Collided(ObjectType _ObjectType)
{
	if (_ObjectType == ObjectType::EnemyBullet)
		{
			//this->health-=10;
			if(health == 0)
				GameObject::SetIsdestroied(true);
			printf("health decreased by 10\n");
	    }
	else if (_ObjectType == ObjectType::Enemy)
	{
		HeroCam->SetEyePosition(this->PreviousPostion);
		this->Move();
		printf("i'm your hero and i collided with enemy \n");
	}
	else if (_ObjectType == ObjectType::MapObject)
	{
		
		HeroCam->SetEyePosition(this->PreviousPostion);
		this->Move();
		printf("i'm your hero and i collided with Mapobject \n");
	}
}

void Hero::Walk_Forward()
{
   this->PreviousPostion = HeroCam->GetEyePosition();
   this->HeroCam->Walk(step);
   this->Move();
}

void Hero::Walk_Backward()
{
	this->PreviousPostion = HeroCam->GetEyePosition();
	this->HeroCam->Walk(-step);
	this->Move();
}

void Hero::Straf_Right()
{
  this->PreviousPostion = HeroCam->GetEyePosition();
  this->HeroCam->Strafe(step);
  this->Move();
}


void Hero::Straf_Left()
{
	this->PreviousPostion = HeroCam->GetEyePosition();
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
