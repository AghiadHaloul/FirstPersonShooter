#ifndef Enemy_h__
#define Enemy_h__

#endif // Enemy_h__
#pragma once
#include "GameComponents/GameObject.h"
#include "MD2Model/md2model.h"
#include<memory>
#include <vector>
#include "CollisionDetection/CollisionManager.h"
#include "GameComponents/Bullet.h"
#include "StaticComponent.h"
#include "CollisionDetection/sensor.h"
using namespace std;

class Enemy : public GameObject , public CollidableModel
{
	float Speed;
	float MaxDist; // max distance in specific direction 
	float Distance;
	int Stamina; 
	
	float fireholdTime;
	float deathTime;
	float FireFrequancy; 
	bool  FireEnable;
	bool isMoving;
	bool isdead;

	animState_t AnimationState;
	void UpdateBoundingbox();
	static CMD2Model  EnemyModel;
	unique_ptr<Sensor> enemySensor; ///enemy collider
    void Move(float deltaTime);
	void InitializeBoundingbox();
	

public:
	Enemy(vec3 mPosition,vec3 mDirection, int stamina, float firefrequancy );
	void Initialize();
	void Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP);
	void UpdateAnimation(float deltaTime);
	virtual void Collided(ObjectType _ObjectType);
	void Fire();
	void Update(float deltaTime);
	void Update_Death(float deltaTime);
	static void Set_EnemyModel();
	~Enemy(void);
	
	// 
	bool bounding(vec3 newpos)
	{
		vec3 NextPosition = newpos;
		return((abs(NextPosition.x) <= 99 && abs(NextPosition.y) <= 99 &&abs(NextPosition.z) <= 99));  
	}
};

