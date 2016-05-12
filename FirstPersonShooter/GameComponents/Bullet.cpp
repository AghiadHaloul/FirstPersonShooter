#include "GameComponents/Bullet.h"


Bullet::Bullet(vec3 mPosition,vec3 Direction,ObjectType BulletType)
	:GameObject(mPosition,Direction)
{
	Speed = 50.0;
	Distance = 0;

   GameObject::Set_InitialTransformation(scale(0.009f,0.009f,0.009f));
   CollidableModel::Set_ObjectType(BulletType);
   
   //calculating bullet bounding box
   CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(BulletModel->VertexData));
   auto tmpboundingbox = CollidableModel::GetBoundingBox();
   tmpboundingbox.Scale(0.009f,0.009f,0.009f);
   tmpboundingbox.SetCenter(GameObject::GetPosition());
   CollidableModel::SetBoundingBox(tmpboundingbox); 

}



void Bullet::Update(float deltatime)
{
	
	float step = Speed*deltatime;
    Distance+=step;
    if(Distance >= MaxDistance)
		GameObject::SetIsdestroied(true);

	vec3 newpos = GameObject::GetPosition()+step*GetDirection();
	GameObject::SetPosition(newpos);
	GameObject::UpdateModelMatrix();
  
	//this kill our game 
	 UpdateBoundingbox(); 	 
}


void Bullet::Render(ShaderProgram * Shader, mat4 VP)
{
	Shader->UseProgram();
	Shader->BindVPMatrix(&VP[0][0]);
	Shader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
	BulletModel->Draw();
}



void Bullet::Set_BulletModel()
{
	BulletModel = new TexturedModel("data/models/Bullet/sphere/spheregold.bmp",10);
	vector<vec3> vertices;
	vector<vec2> UVData;
	vector<vec3> normals;
	loadOBJ("data/models/Bullet/sphere/sphere.obj",vertices,UVData,normals);
	BulletModel->VertexData = vertices;
	BulletModel->UVData = UVData;
	BulletModel->NormalsData=normals;
	BulletModel->Initialize();
}
TexturedModel* Bullet::BulletModel = nullptr; //must for static members


void Bullet::UpdateBoundingbox()
{
	auto tmpboundingbox = CollidableModel::GetBoundingBox();
	tmpboundingbox.SetCenter(GameObject::GetPosition());
	CollidableModel::SetBoundingBox(tmpboundingbox);
}


void Bullet::Collided(ObjectType _ObjectType)
{
	if (_ObjectType == ObjectType::Enemy && CollidableModel::Get_ObjectType()==ObjectType::HeroBullet)
    {
	   printf("i'm  the hero bullet and I collided with enemy and i'm gonna be destroyed now bye bye  \n");
	   GameObject::SetIsdestroied(true);   
	}
	else if (_ObjectType == ObjectType::Hero && CollidableModel::Get_ObjectType()==ObjectType::EnemyBullet)
	{
		GameObject::SetIsdestroied(true); 
	}
	else if (_ObjectType == ObjectType::MapObject)
	{
		GameObject::SetIsdestroied(true); 
	}
}

Bullet::~Bullet(void)
{
}
