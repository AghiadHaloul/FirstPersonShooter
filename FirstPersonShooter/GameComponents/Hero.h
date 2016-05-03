#pragma once
#ifndef Hero_h__
#define Hero_h__
#endif // Hero_h__
#include "EulerCamera/EulerCamera.h"
#include "GameComponents/GameObject.h"
#include "MD2Model/md2model.h"
#include <memory>
#include "Model3D/Model3D.h"
#include "GameComponents/Bullet.h"
#include <iostream>
#include <vector>
#include "CollisionDetection/CollisionManager.h"
using namespace std;

class Hero : public CMD2Model , public GameObject
{
    vector<Bullet*>Ammo;
	animState_t AnimationState;
	float step;

	void UpdateBoundingbox();
	void Move();
	
public:
	unique_ptr<EulerCamera> HeroCam;
	Hero();
	Hero(vec3 mPosition,vec3 mDirection);
	
	void Initialize();
	void Render(ShaderProgram * shader,mat4 VP);
	void Update(unique_ptr<CollisionManager>&collisionManager,float deltaTime);
	void Fire(unique_ptr<CollisionManager>& collisionManager);
	virtual void Collided(ObjectType _ObjectType);
	void UpdateAnimation(float deltaTime);


	void Walk_Forward();
	void Walk_Backward();

	void Straf_Right(); 
	void Straf_Left(); 
	void Yaw(double deltaX);
	void Pitch(double deltaY);
	vec3 get_heropos();
	~Hero(void);
	
};

