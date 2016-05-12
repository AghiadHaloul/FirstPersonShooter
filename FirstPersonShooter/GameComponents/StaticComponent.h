#include "CollisionDetection/CollisionManager.h"
#include "GameComponents/Bullet.h"
#include "ShaderProgram/ShaderProgram.h"
#include <vector>
#include <memory>
using namespace std;

class SceneBullets
{
	vector<Bullet*> AllBullets;	
public:
	void AddBullet(Bullet* Newbullet);
	void Update(float deltaTime);
	void Render(ShaderProgram*shader,mat4 VP);

	SceneBullets(void);
	~SceneBullets(void);
};

///////////////////////////////////////////
///////////////// ///////////////////////////
class StaticComponent
{
public:

	StaticComponent();
	~StaticComponent();
	 
	static unique_ptr<CollisionManager> collisionManager;
	static unique_ptr<SceneBullets> sceneBullets;
private:

};

