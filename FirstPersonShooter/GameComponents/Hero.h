#pragma once
#ifndef Hero_h__
#define Hero_h__
#endif // Hero_h__
#include "GameComponents/GameObject.h"
#include "MD2Model/md2model.h"
#include <memory>
using namespace std;

class Hero : public CMD2Model , public GameObject
{
	animState_t AnimationState;
	KeyFrameAnimationShader *shader;
    void UpdateBoundingbox();
public:
	Hero(KeyFrameAnimationShader *mshader);
	Hero(KeyFrameAnimationShader *mshader,vec3 mPosition,vec3 mDirection,bool misdestroied = false);
	void UpdateAnimation(float deltaTime);
	void Initialize();
	void Render(mat4 VP);
	void Collided(ObjectType _ObjectType);
	void Move(vec3 NewDirection);
	
	~Hero(void);
	

};

