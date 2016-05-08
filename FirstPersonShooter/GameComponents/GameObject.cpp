#include "GameObject.h"


GameObject::GameObject(void)
{
	this->SetPosition(vec3(0));
	this->SetDirection(vec3(0.0,0.0,-1.0));
	this->SetIsdestroied(false);
   //default 
	UpdateModelMatrix();
}

GameObject::GameObject(vec3 mPosition,vec3 mDirection)
{
	this->Position = mPosition;
	this->SetDirection(mDirection);
	this->SetIsdestroied(false);
	//default
  UpdateModelMatrix();
}


GameObject::~GameObject()
{
}

void GameObject::UpdateModelMatrix()

{
	//badrb fi -1 3shan a match Right hand rule
	//float angle = glm::orientedAngle(GetDirection(),vec3(1,0,0),vec3(1,0,0));
    float angle = atan2(GetDirection().z*-1,GetDirection().x)*180/PI;
	this->Set_XZ_DirectionAngle(angle);	
	
	//this->Set_YZ_DirectionAngle(atan2(GetDirection().z,GetDirection().y)*180/PI);	
	//this->Set_XY_DirectionAngle(atan2(GetDirection().x,GetDirection().y)*180/PI);	

	this->Set_ModelMatrix(
		translate(GetPosition())
		*rotate(Get_XZ_DirectionAngle(),vec3(0,1,0))
		*Get_InitialTransformation());
//	*rotate(Get_XY_DirectionAngle(),vec3(0,0,1))
}
