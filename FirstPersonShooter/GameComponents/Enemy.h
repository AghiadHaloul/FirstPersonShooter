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
using namespace std;

class Enemy : public GameObject , public CollidableModel
{

	animState_t AnimationState;
	void UpdateBoundingbox();
	vector<Bullet*>Ammo;
	static CMD2Model  EnemyModel;
	//float step;
	//void Move();
public:
	Enemy(vec3 mPosition,vec3 mDirection );
	void Initialize();
	void Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP);
	void UpdateAnimation(float deltaTime);
	virtual void Collided(ObjectType _ObjectType);
	void Fire(unique_ptr<CollisionManager>& collisionManager);
	void Update(unique_ptr<CollisionManager>&collisionManager,float deltaTime);
	static void Set_EnemyModel();
	~Enemy(void);
};

