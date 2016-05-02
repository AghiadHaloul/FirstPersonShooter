#ifndef Enemy_h__
#define Enemy_h__

#endif // Enemy_h__
#pragma once
#include "GameComponents/GameObject.h"
#include "MD2Model/md2model.h"

class Enemy : public GameObject , public CMD2Model
{

	animState_t AnimationState;
	void UpdateBoundingbox();
	//float step;
	//void Move();
public:
	void Initialize();
	void Render(KeyFrameAnimationShader *shader,mat4 VP);
	void UpdateAnimation(float deltaTime);
	virtual void Collided(ObjectType _ObjectType);
	Enemy(vec3 mPosition,vec3 mDirection );
	~Enemy(void);
};

