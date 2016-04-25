#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


#include "Shaders/shader.hpp"
#include "Model/Model.h"
#include "EulerCamera/EulerCamera.h"
#include "Cube/Cube.h"
#include "Texture/texture.h"
#include "ShaderProgram/ShaderProgram.h"
#include "Scene/Model3D.h"
#include"SkyBox/SkyBox.h"
#include "MD2Model/md2model.h"
#include "CollisionDetection/CollisionManager.h"
#include "GameComponents/Hero.h"
using namespace std;
class Renderer
{//removed later
	//CMD2Model blade;
	//animState_t bladeAnimationState;
	std::unique_ptr<CollisionManager> collisionManager;
	//glm::mat4 bladeM;
	KeyFrameAnimationShader animatedModelShader;
	unique_ptr<Model3D> house;
	glm::mat4 houseM;
	//
    unique_ptr<Hero> hero;
    GLuint programID;
    ShaderProgram shader;
	// Transformation
	//GLuint MatrixID;
	GLuint ModelMatrixID;
	GLuint AmbientLightID;
	GLuint LightPositionID;
	GLuint EyePositionID;

	std::unique_ptr<SkyBox> Game_SkyBox;
	

	unique_ptr<Model3D> soldier;

	std::unique_ptr<EulerCamera> myCamera;

	glm::vec3 ambientLight;
	glm::vec3 lightPosition;

public:
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY);
	void Update(double deltaTime);
    void Cleanup();
};

#endif // Renderer_h__

