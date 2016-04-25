#include "Cube/Cube.h"
class SkyBox
{

private:
	unique_ptr<TexturedModel>* walls;
	
public:
	GLfloat Unitsize;
	SkyBox(GLfloat unitsize);
	~SkyBox();
	void Draw(ShaderProgram &shader);
	void Initialize();
	void Cleanup();
};

