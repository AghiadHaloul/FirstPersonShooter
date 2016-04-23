#include "Cube/Cube.h"
class SkyBox
{

private:
	unique_ptr<Cube>* walls; 
public:
    GLuint unitSize;
	SkyBox(GLint unitsize);
	~SkyBox();
	void Draw(ShaderProgram &shader);
	void Initialize();
};

