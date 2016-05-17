#include "CollisionDetection/CollisionManager.h"
#include "GameComponents/Bullet.h"
#include "ShaderProgram/ShaderProgram.h"
#include <vector>
#include <memory>
#include "sound/SoundEngine.h"

using namespace std;

class SceneBullets
{
	vector<Bullet*> AllBullets;	
public:
	void AddBullet(Bullet* Newbullet);
	void Update(float deltaTime);
	void Render(ShaderProgram*shader,mat4 VP);
	void Cleanup();
	SceneBullets(void);
	~SceneBullets(void);
};

///////////////////////////////////////////
///////////////// ///////////////////////////
class StaticComponent
{
public:
	enum GameLevel {Level1,Level2}; 

	StaticComponent();
	~StaticComponent();
    static GameLevel Current_Level;
	static unique_ptr<SoundEngine> soundEngine;
	static unique_ptr<CollisionManager> collisionManager;
	static unique_ptr<SceneBullets> sceneBullets;
	static float RepeatTime;
	static float PlayingTime;
	static bool LevelCompleted;

private:

};

