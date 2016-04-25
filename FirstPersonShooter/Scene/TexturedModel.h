#ifndef TexturedModel_h__
#define TexturedModel_h__

#include <glm/glm.hpp>
#include <vector>
#include <gl\glew.h>
#include "Texture\texture.h"
#include "ShaderProgram\ShaderProgram.h"
#include "Model\Model.h"
using namespace std;
class TexturedModel : public Model
{
	
public:
	TexturedModel();
	TexturedModel(string TexturePath,int TextUnit);
	~TexturedModel();
	Texture* texture;
	 void Draw();
};
#endif // Model_h__

