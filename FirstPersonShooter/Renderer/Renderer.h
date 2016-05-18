#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Shaders/shader.hpp"
#include "ShaderProgram/ShaderProgram.h"
#include"SkyBox/SkyBox.h"
#include "CollisionDetection/CollisionManager.h"
#include "GameComponents/Hero.h"
#include "GameScene/Level1.h"
#include "GameScene/Level2.h"
#include "text2D.hpp"

 
using namespace std;
class Renderer
{
	
	
	unique_ptr<Hero> hero;
	std::unique_ptr<SkyBox> Game_SkyBox;
	unique_ptr<Level1> Firstlevel;
	unique_ptr<Level2> Secondlevel;
    KeyFrameAnimationShader animatedModelShader;
	ShaderProgram shader;
	
	glm::vec3 ambientLight;
	vector<vec3> lightPositions;
	vector<vec3> lightcolors;
	unique_ptr<TexturedModel> CorssModel;
    unique_ptr<SoundEngine> soundEngine;
	

	//sound* audio;
	//unsigned int audioID;
public:
    bool GameOver;

	Renderer();
    ~Renderer();
    
    void Initialize();
	void Initialize_CrossHair();
	void Draw();
	void DrawText();
	void Draw_CrossHair();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY,static bool LeftBtn_clicked);
	void Update(double deltaTime);
    void Cleanup();
	
};

#endif // Renderer_h__

