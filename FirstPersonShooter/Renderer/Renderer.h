#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>


#include "shader.hpp"
#include "Model.h"
#include "EulerCamera.h"
#include "Cube.h"
#include "texture.h"
#include "ShaderProgram.h"
#include "Model3D.h"
#include "SkyBox.h"
using namespace std;
class Renderer
{
    
    
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
    
    bool CheckCameraPosition(glm::vec3,GLuint,int);
    void Initialize();
    void Draw();
    void HandleKeyboardInput(int key);
    void HandleMouse(double deltaX,double deltaY);
    void Update(double deltaTime);
    void Cleanup();
};

#endif // Renderer_h__

