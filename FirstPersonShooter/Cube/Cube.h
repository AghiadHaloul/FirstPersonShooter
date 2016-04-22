#ifndef Cube_h__
#define Cube_h__

#include "Model\Model.h"
#include "ShaderProgram/ShaderProgram.h"
#include "Texture/texture.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene/TexturedModel.h"
using namespace std;
using namespace glm;
class Cube
{
	TexturedModel* mSquare;
	vector<mat4> mFacesModelMatrices;
public:
	Cube(string TexturePath,int TextUnit,vec3 Translate, vec3 Scale);
	~Cube(void);

	glm::mat4 CubeModelMatrix;
	void Initialize();
	void Draw(ShaderProgram &shader);
	void Cleanup();
};

#endif // Cube_h__
