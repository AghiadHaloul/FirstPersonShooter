#include "GameComponents/GameObject.h"
#include "Model3D/Model3D.h"
#include <memory>
using namespace std;
class SkyBox : public GameObject , public Model3D 
{
	unique_ptr<TexturedModel> ground;
public:
	SkyBox();
	~SkyBox();
	void Render(ShaderProgram * Shader, mat4 VP);
	void Initialize();
	void SetModel();
	void Set_Ground();
	void Cleanup();
	virtual void Collided(ObjectType _ObjectType);
};

