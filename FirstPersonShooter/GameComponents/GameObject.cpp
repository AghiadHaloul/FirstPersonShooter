#include "GameObject.h"


GameObject::GameObject(void)
{
	this->SetPosition(vec3(0));
	this->SetDirection(vec3(-1.0,0.0,.0));
	this->SetIsdestroied(false);
   //default 
	this->Set_InitialTransformation(glm::rotate(-90.0f,1.0f,0.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
	UpdateModelMatrix();
}

GameObject::GameObject(vec3 mPosition,vec3 mDirection,bool misdestroied = false)
{
	this->Position = mPosition;
	this->SetDirection(mDirection);
	//default
	this->Set_InitialTransformation(glm::rotate(-90.0f,1.0f,0.0f,0.0f) * glm::scale(0.01f,0.01f,0.01f));
    UpdateModelMatrix();
}


GameObject::~GameObject()
{
}

void GameObject::UpdateModelMatrix()
{
	//badrb fi -1 3shan a match Right hand rule
	this->SetDirectionAngle(atan2(GetDirection().z*-1,GetDirection().x)*180/PI);	
	this->Set_ModelMatrix(
		translate(GetPosition())
		*rotate(GetDirectionAngle(),vec3(0,1,0))
		*Get_InitialTransformation());
}
