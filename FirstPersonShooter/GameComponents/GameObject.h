#pragma once
#ifndef GameObject_h__
#define GameObject_h__
#endif // GameObject_h__
#include <glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <math.h>
#include <iostream>
using namespace std;
//#include <gl/GL.h>
using namespace glm;
class GameObject
{
#define PI 3.14159265359
protected:
	mat4 ModelMatrix;
	mat4 InitialTransformation; //resize the object to fit in our game
private:
	
	float XZ_DirectionAngle;
	float YZ_DirectionAngle;
	float XY_DirectionAngle; 

	bool isdestroied;
 public:
	 vec3 Direction;
	 vec3 Position;
	 GameObject::GameObject(vec3,vec3 );
	GameObject(void);
	~GameObject(void);
	void UpdateModelMatrix();
	glm::vec3 GetDirection() const { return Direction; }
	void SetDirection(glm::vec3 val) { Direction = normalize(val); }
	glm::vec3 GetPosition() const { return Position; }
	void SetPosition(glm::vec3 val) { Position = val; }
	bool GetIsdestroied() const { return isdestroied; }
	void SetIsdestroied(bool val) { isdestroied = val; }
	glm::mat4 Get_InitialTransformation() const { return InitialTransformation; }
	void Set_InitialTransformation(glm::mat4 val) { InitialTransformation = val; }
	glm::mat4 Get_ModelMatrix() const { return ModelMatrix; }
	void Set_ModelMatrix(glm::mat4 val) { ModelMatrix = val; }
	float Get_YZ_DirectionAngle() const { return YZ_DirectionAngle; }
	void Set_YZ_DirectionAngle(float val) { YZ_DirectionAngle = val; }
	float Get_XZ_DirectionAngle() const { return XZ_DirectionAngle; }
	void Set_XZ_DirectionAngle(float val) { XZ_DirectionAngle = val; }
	//float Get_XY_DirectionAngle() const { return XY_DirectionAngle; }
	//void Set_XY_DirectionAngle(float val) { XY_DirectionAngle = val; }
};

