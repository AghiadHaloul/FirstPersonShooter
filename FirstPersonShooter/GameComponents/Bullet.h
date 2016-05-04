#pragma once
#ifndef Bullet_h__
#define Bullet_h__

#endif // Bullet_h__

#include "GameComponents/GameObject.h"
#include "Model/TexturedModel.h"
#include "CollisionDetection/CollidableModel.h"
#include <vector>
#include "OBJLoader/objloader.hpp"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
// dont forget try to edit in updating bounding box  and make the model static
class Bullet :public GameObject , public CollidableModel
{
  #define  MaxDistance 50
  float Speed;
  float Damage;
  float Distance;

   static TexturedModel* BulletModel; // static model for all bullets
public:
	Bullet( vec3 mPosition,vec3 Direction,ObjectType BulletType);
	void Update(float deltatime);
	void Render(ShaderProgram * Shader , mat4 VP);
	static void Set_BulletModel(); 
	void UpdateBoundingbox();
   virtual void Collided(ObjectType _ObjectType);
	~Bullet(void);
};

