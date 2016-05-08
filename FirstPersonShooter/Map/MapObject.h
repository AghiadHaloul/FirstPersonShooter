#pragma once
#ifndef MapObject_h
#define MapObject_h

#include "GameComponents/GameObject.h"
#include "Model/TexturedModel.h"
#include "CollisionDetection/CollidableModel.h"
#include "OBJLoader/objloader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Model3D/Model3D.h"
using namespace glm;

class MapObject : public GameObject , public CollidableModel
{
    //static TexturedModel* MapObjectModel;
    static Model3D MapObjectModel;
public:
    MapObject(vec3 Position,vec3 Direction);
    void Render(ShaderProgram*, mat4);
    static void Set_Model();
    virtual void Collided(ObjectType);
    ~MapObject(void);
};

#endif /* MapObject_h */
