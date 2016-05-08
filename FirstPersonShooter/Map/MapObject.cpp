#include "MapObject.h"


Model3D MapObject::MapObjectModel ;
//TexturedModel* MapObject::MapObjectModel = nullptr;

MapObject::MapObject(vec3 mPosition,vec3 Direction):GameObject(mPosition,Direction)
{
    GameObject::Set_InitialTransformation(scale(0.1f,0.1f,0.1f));
	GameObject::UpdateModelMatrix();

	CollidableModel::Set_ObjectType(ObjectType::MapObject);
    CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(MapObjectModel.GetVertices()));
	auto boundingbox = CollidableModel::GetBoundingBox();
    boundingbox.Scale(0.1f,0.1f,0.1f);
    boundingbox.SetCenter(GameObject::GetPosition());
    CollidableModel::SetBoundingBox(boundingbox);
}

void MapObject::Render(ShaderProgram * Shader, mat4 VP)
{
    Shader->UseProgram();
    Shader->BindVPMatrix(&VP[0][0]);
    Shader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
	//MapObjectModel->Draw();
	  MapObjectModel.Render(Shader,GameObject::Get_ModelMatrix(),mat4(1));
}

void MapObject::Set_Model()
{/*
    MapObjectModel = new TexturedModel("data/models/House/house.jpg",50);
    vector<vec3> vertices;
    vector<vec2> UVData;
    vector<vec3> normals;
    loadOBJ("data/models/House/house.3ds",vertices,UVData,normals);
    MapObjectModel->VertexData = vertices;
    MapObjectModel->UVData = UVData;
    MapObjectModel->NormalsData = normals;
    MapObjectModel->Initialize();
	cout<<"tree loaded"<<endl;
	*/
	MapObjectModel =  Model3D();
	MapObjectModel.LoadFromFile("data/models/house/AranHouse1_3ds.3ds",true);
    MapObjectModel.Initialize();
}

void MapObject::Collided(ObjectType _ObjectType)
{
    if (_ObjectType == ObjectType::Hero)
    {
        printf("I'm a map object and hero collided with me\n");
    }
	
	else if (_ObjectType == ObjectType::HeroBullet)
	{
		printf("I'm a map object and hero bullet collided with me\n");
	}

}

MapObject::~MapObject(void){}
