#pragma once
#ifndef Level1_h__
#define Level1_h__

#endif // Level1_h__
#include "GameScene/GameScene.h"

class Level2 :public GameScene
{
public:
	Level2();
	virtual void Initialize();
	virtual void Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP) ;
	virtual void Update(float deltatime);

	virtual void Initialize_Enemies();
	virtual void Update_Enemies(float deltatime);
	virtual void Render_Enemies(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP);

	virtual void Initialize_MapObjects();
	virtual void Update_MapObjects();
	virtual void Render_MapObjects(ShaderProgram*StaticShader,mat4 VP);

	~Level2(void);
};

