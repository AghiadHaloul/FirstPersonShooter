#include "MapObject.h"


Model3D MapObject::BuildingModel;
TexturedModel* MapObject::TreeModel = nullptr;
//TexturedModel* MapObject::MapObjectModel = nullptr;

MapObject::MapObject(vec3 mPosition,vec3 Direction,MapObjectType MapObjectType_):GameObject(mPosition,Direction)
{
	this->MapObjectType_ = MapObjectType_;
	if(MapObjectType_==MapObjectType::building1){
		GameObject::Set_InitialTransformation(scale(0.03f,0.03f,0.03f));
		GameObject::UpdateModelMatrix();

		CollidableModel::Set_ObjectType(ObjectType::MapObject);
		CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(BuildingModel.GetVertices()));
		auto boundingbox = CollidableModel::GetBoundingBox();
		boundingbox.Scale(0.03f,0.03f,0.03f);
		boundingbox.SetCenter(GameObject::GetPosition());
		CollidableModel::SetBoundingBox(boundingbox);
	}
	else if(MapObjectType_==MapObjectType::tree){
		GameObject::Set_InitialTransformation(scale(0.01f,0.01f,0.01f));
		GameObject::UpdateModelMatrix();

		CollidableModel::Set_ObjectType(ObjectType::MapObject);
		CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(TreeModel->VertexData));
		auto boundingbox = CollidableModel::GetBoundingBox();
		boundingbox.Scale(0.01f,0.01f,0.01f);
		boundingbox.SetCenter(GameObject::GetPosition());
		CollidableModel::SetBoundingBox(boundingbox);
	}
}

void MapObject::Render(ShaderProgram * Shader, mat4 VP)
{
	Shader->UseProgram();
	Shader->BindVPMatrix(&VP[0][0]);
	Shader->BindModelMatrix(&GameObject::Get_ModelMatrix()[0][0]);
	
	if(MapObjectType_==MapObjectType::building1){
		BuildingModel.Render(Shader,GameObject::Get_ModelMatrix(),mat4(1));
		cout<<"Building Rendered\n";
	}
	else if(MapObjectType_==MapObjectType::tree){
		TreeModel->Draw();
	}
}

void MapObject::Set_Model()
{
	TreeModel = new TexturedModel("data/models/Tree/Tree.jpg",50);
	vector<vec3> vertices;
	vector<vec2> UVData;
	vector<vec3> normals;
	loadOBJ("data/models/Tree/Tree.obj",vertices,UVData,normals);
	TreeModel->VertexData = vertices;
	TreeModel->UVData = UVData;
	TreeModel->NormalsData = normals;
	TreeModel->Initialize();
	cout<<"tree loaded"<<endl;
	
	BuildingModel =  Model3D();
	BuildingModel.LoadFromFile("data/models/house/AranHouse1_3ds.3ds",true);
	BuildingModel.Initialize();
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
