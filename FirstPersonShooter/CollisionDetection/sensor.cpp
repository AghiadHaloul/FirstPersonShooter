#include "sensor.h"


Model* Sensor::sensormodel = nullptr;
vec3 Sensor::HeroPostion;
Sensor::Sensor(vec3*position, vec3*direction,bool* enableFire, bool* isMoving)
{
	this->Position = position;
	this->Direction = direction;
	this->EnableFire = enableFire;
	this->isMoving = isMoving;
	Initialize_BoundingBox();
}

void Sensor::Initialize_BoundingBox()
{
	CollidableModel::Set_ObjectType(ObjectType::EnemySensor);
	CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(sensormodel->VertexData));
	auto boundingbox = CollidableModel::GetBoundingBox();
	boundingbox.Scale(50.f,50.f,50.0f);
	boundingbox.SetCenter(*Position);
	CollidableModel::SetBoundingBox(boundingbox);
}

void Sensor::Update_BoundingBox()
{
	auto boundingbox = CollidableModel::GetBoundingBox();
	boundingbox.SetCenter(*Position);
	CollidableModel::SetBoundingBox(boundingbox);
	//cout<<"sensor  X "<<(*Position).x;
	//cout<<"  Y "<<(*Position).y;
	//cout<<"  Z "<<(*Position).z <<endl;

}
void Sensor::Collided(ObjectType _ObjectType)
{
	if(_ObjectType==ObjectType::Hero)
	{
		//cout<<"iam a sensor colided with hero"<<endl;
	    (*EnableFire)=true;
		*this->isMoving = false;
		vec3 Enemyposxz = vec3((*Position).x,0,(*Position).z);
		vec3 heading = Sensor::HeroPostion-Enemyposxz ;
		(*Direction) = normalize(heading);
		printf("enemysensor collided with hero \n ");
	}
	else if(_ObjectType==ObjectType::HeroBullet)
	{
		//cout<<"iam a sensor colided with hero"<<endl;
		(*EnableFire)=true;
		vec3 Enemyposxz = vec3((*Position).x,0,(*Position).z);
		vec3 heading = Sensor::HeroPostion-Enemyposxz ;
		(*Direction) = normalize(heading);
		printf("enemysensor collided with hero \n ");
	}
}
void Sensor::Set_Model()
{
    sensormodel = new Model();
    vector<vec3> vertices;
    vector<vec2> UVData;
    vector<vec3> normals;
    loadOBJ("data/models/cube/cube.obj",vertices,UVData,normals);
    sensormodel->VertexData = vertices;
    sensormodel->UVData = UVData;
    sensormodel->NormalsData = normals;
    sensormodel->Initialize();
	//cout<<"tree loaded"<<endl;
}



Sensor::~Sensor(void)
{
}

