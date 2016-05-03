#ifndef CollidableModel_h__
#define CollidableModel_h__

#include "AABoundingBox.h"
#include <vector>
#include <glm\glm.hpp>

class CollidableModel
{
public:
	enum ObjectType{MD2model,MapObject,HeroBullet,EnemyBullet,Hero,Enemy};

private:
	AABoundingBox boundingBox;
	ObjectType _ObjectType;
public:

	CollidableModel(void);
	~CollidableModel(void);
	
	ObjectType Get_ObjectType() const { return _ObjectType; }
	void Set_ObjectType(ObjectType val) { _ObjectType = val; }

	void SetBoundingBox(AABoundingBox fBoundingBox) { boundingBox = fBoundingBox;}
	AABoundingBox GetBoundingBox(){ return boundingBox;}
	//calculates the bounding box of a set of vertices. the box's size can be increased/decreased using the parameter boxOffset.
	static AABoundingBox CalculateBoundingBox(std::vector<glm::vec3> vertices, float boxOffset = 0.0f);
	//handles collision, is virtual since each derived class handle collision differently.
	virtual void Collided(ObjectType _ObjectType);
};
#endif // CollidableModel_h__

