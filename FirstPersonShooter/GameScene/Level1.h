#pragma once
#ifndef Level1_h__
#define Level1_h__

#endif // Level1_h__
#include "GameScene/GameScene.h"
class Level1 :public GameScene
{
public:
	Level1(unique_ptr<CollisionManager>& collisionManager);
	virtual void Initialize(unique_ptr<CollisionManager>& collisionManager);
	virtual void Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP) ;
	virtual void Update(unique_ptr<CollisionManager>& collisionManager,float deltatime);

	virtual void Initialize_Enemies(unique_ptr<CollisionManager>& collisionManager);
	virtual void Update_Enemies(unique_ptr<CollisionManager>& collisionManager,float deltatime);
	virtual void Render_Enemies(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP);

	virtual void Initialize_MapObjects(unique_ptr<CollisionManager>& collisionManager);
	virtual void Update_MapObjects(unique_ptr<CollisionManager>& collisionManager);
	virtual void Render_MapObjects(ShaderProgram*StaticShader,mat4 VP);

	~Level1(void);
};

