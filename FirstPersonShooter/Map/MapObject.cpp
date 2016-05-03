#include "MapObject.h"


TexturedModel* MapObject::MapObjectModel = nullptr;

MapObject::MapObject(vec3 mPosition,vec3 Direction):GameObject(mPosition,Direction)
{
    GameObject::Set_InitialTransformation(scale(0.01f,0.01f,0.01f));
	GameObject::UpdateModelMatrix();

	CollidableModel::Set_ObjectType(ObjectType::MapObject);
    CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(MapObjectModel->VertexData));
	auto boundingbox = CollidableModel::GetBoundingBox();
    boundingbox.Scale(0.01f,0.01f,0.01f);
    boundingbox.SetCenter(GameObject::GetPosition());
    CollidableModel::SetBoundingBox(boundingbox);

}

void MapObject::Render(ShaderProgram * Shader, mat4 VP)
{
    Shader->UseProgram();
    Shader->BindVPMatrix(&VP[0][0]);
    Shader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
    MapObjectModel->Draw();
}

void MapObject::Set_Model()
{
    MapObjectModel = new TexturedModel("data/models/Tree/Tree.jpg",50);
    vector<vec3> vertices;
    vector<vec2> UVData;
    vector<vec3> normals;
    loadOBJ("data/models/Tree/Tree.obj",vertices,UVData,normals);
    MapObjectModel->VertexData = vertices;
    MapObjectModel->UVData = UVData;
    MapObjectModel->NormalsData = normals;
    MapObjectModel->Initialize();
	cout<<"tree loaded"<<endl;
}

void MapObject::Collided(ObjectType _ObjectType)
{
    if (_ObjectType == ObjectType::Hero && CollidableModel::Get_ObjectType()==ObjectType::MapObject)
    {
        printf("I'm a map object and hero collided with me\n");
    }
}

MapObject::~MapObject(void){}
