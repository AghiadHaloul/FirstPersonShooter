#pragma once
#include "CollisionDetection/CollidableModel.h"
#include <glm/glm.hpp>
#include "Model/Model.h"
#include <vector>
#include "OBJLoader/objloader.hpp"
#include <iostream>
using namespace glm;
using namespace std;
class Sensor:public CollidableModel
{
	vec3*Position;
	vec3*Direction;
	bool* EnableFire;
	static Model* sensormodel;
	
public:
	static vec3 HeroPostion;
	Sensor(vec3*position, vec3*direction,bool* enableFire);
	~Sensor(void);
     virtual void Collided(ObjectType _ObjectType);
	 static void Set_Model();
	 void Update_BoundingBox();
	 void Initialize_BoundingBox();
};

