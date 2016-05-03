#pragma once
#ifndef GameScene_h__
#define GameScene_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "GameComponents/Enemy.h"
#include "Map/MapObject.h"

using namespace std;

#endif // GameScene_h__
class GameScene
{
protected:
	vector<Enemy*> Enemies;
	vector<MapObject*> MapObjects;
	//vector<mapobject*>map;
	
public:

	GameScene();
	virtual void Initialize(unique_ptr<CollisionManager>& collisionManager);
	virtual void Render(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP) ;
	virtual void Update(unique_ptr<CollisionManager>& collisionManager,float deltatime);

	virtual void Initialize_Enemies(unique_ptr<CollisionManager>& collisionManager);
	virtual void Update_Enemies(unique_ptr<CollisionManager>& collisionManager,float deltatime);
	virtual void Render_Enemies(ShaderProgram*StaticShader,KeyFrameAnimationShader *AnimationShader,mat4 VP);

	virtual void Initialize_MapObjects(unique_ptr<CollisionManager>& collisionManager);
	virtual void Update_MapObjects(unique_ptr<CollisionManager>& collisionManager);
	virtual void Render_MapObjects(ShaderProgram*StaticShader,mat4 VP);
	
	~GameScene(void);
};

