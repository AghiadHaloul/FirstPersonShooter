#include "CrossHair.h"





CrossHair::CrossHair(vec3 mpostion):GameObject(mpostion,vec3(1,0,0))
{
	GameObject::Set_InitialTransformation(scale(vec3(0.01)));
	GameObject::UpdateModelMatrix();
    Initialize();
}

void CrossHair::Initialize()
{
	CrossHairModel = new TexturedModel("data/models/Bullet/sphere/sphereblack.bmp",10);
	vector<vec3> vertices;
	vector<vec2> UVData;
	vector<vec3> normals;
	loadOBJ("data/models/Bullet/sphere/sphere.obj",vertices,UVData,normals);
	CrossHairModel->VertexData = vertices;
	CrossHairModel->UVData = UVData;
	CrossHairModel->NormalsData=normals;
	CrossHairModel->Initialize();
}

void CrossHair::Render(ShaderProgram* StaticShader,mat4 VP)
{
	StaticShader->UseProgram();
	StaticShader->BindVPMatrix(&VP[0][0]);
	StaticShader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
    CrossHairModel->Draw();
	cout << "corss renders" <<endl;
}


void CrossHair::Move(vec3 mpostion)
{
	GameObject::SetPosition(mpostion);
	GameObject::UpdateModelMatrix();
}

CrossHair::~CrossHair(void)
{
}
