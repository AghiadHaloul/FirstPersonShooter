#include "Cube/Cube.h"
class SkyBox
{

private:
	unique_ptr<Cube>* walls; 
public:
	SkyBox(GLint unitsize);
	~SkyBox();
	void Draw(ShaderProgram &shader);
	void Initialize();
};

