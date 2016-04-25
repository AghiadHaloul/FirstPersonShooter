#pragma once
#ifndef GameObject_h__
#define GameObject_h__
#endif // GameObject_h__
#include <glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include <math.h>

//#include <gl/GL.h>
using namespace glm;
class GameObject
{
#define PI 3.14159265359
protected:
	mat4 ModelMatrix;
	mat4 InitialTransformation; //resize the object to fit in our game
private:
	vec3 Direction;
	vec3 Position;
	float DirectionAngle;
	bool isdestroied;
 public:
	 GameObject::GameObject(vec3,vec3 ,bool);
	GameObject(void);
	~GameObject(void);
	void UpdateModelMatrix();
	glm::vec3 GetDirection() const { return Direction; }
	void SetDirection(glm::vec3 val) { Direction = val; }
	glm::vec3 GetPosition() const { return Position; }
	void SetPosition(glm::vec3 val) { Position = val; }
	float GetDirectionAngle() const { return DirectionAngle; }
	void SetDirectionAngle(float val) { DirectionAngle = val; }
	bool GetIsdestroied() const { return isdestroied; }
	void SetIsdestroied(bool val) { isdestroied = val; }
	glm::mat4 Get_InitialTransformation() const { return InitialTransformation; }
	void Set_InitialTransformation(glm::mat4 val) { InitialTransformation = val; }
	glm::mat4 Get_ModelMatrix() const { return ModelMatrix; }
	void Set_ModelMatrix(glm::mat4 val) { ModelMatrix = val; }
};

