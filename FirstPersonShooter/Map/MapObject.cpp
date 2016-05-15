#include "MapObject.h"


Model3D MapObject::BuildingModel;
Model3D MapObject::BuildingMode2;

Model3D MapObject::TreeModel;
Model3D MapObject::Car;


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
	else if(MapObjectType_==MapObjectType::building2){
		GameObject::Set_InitialTransformation(scale(0.1f,0.1f,0.1f));
		GameObject::UpdateModelMatrix();

		CollidableModel::Set_ObjectType(ObjectType::MapObject);
		CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(BuildingMode2.GetVertices()));
		auto boundingbox = CollidableModel::GetBoundingBox();
		boundingbox.Scale(0.1f,0.1f,0.1f);
		boundingbox.SetCenter(GameObject::GetPosition());
		CollidableModel::SetBoundingBox(boundingbox);
	}
	else if(MapObjectType_==MapObjectType::tree){
		GameObject::Set_InitialTransformation(scale(2.0f,2.0f,2.0f));
		GameObject::UpdateModelMatrix();

		CollidableModel::Set_ObjectType(ObjectType::MapObject);
		CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(TreeModel.GetVertices()));
		auto boundingbox = CollidableModel::GetBoundingBox();
		boundingbox.Scale(2.0f,2.0f,2.0f);
		boundingbox.SetCenter(GameObject::GetPosition());
		CollidableModel::SetBoundingBox(boundingbox);
	}

	else if(MapObjectType_==MapObjectType::car){
		GameObject::Set_InitialTransformation(scale(0.1f,0.1f,0.1f));
		GameObject::UpdateModelMatrix();

		CollidableModel::Set_ObjectType(ObjectType::MapObject);
		CollidableModel::SetBoundingBox(CollidableModel::CalculateBoundingBox(Car.GetVertices()));
		auto boundingbox = CollidableModel::GetBoundingBox();
		boundingbox.Scale(0.1f,0.1f,0.1f);
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
		//cout<<"Building Rendered\n";
	}
	else if(MapObjectType_==MapObjectType::building2){
		BuildingMode2.Render(Shader,GameObject::Get_ModelMatrix(),mat4(1));
		//cout<<"Building Rendered\n";
	}
	else if(MapObjectType_==MapObjectType::tree){
		TreeModel.Render(Shader,GameObject::Get_ModelMatrix(),mat4(1));
	}
	else if(MapObjectType_==MapObjectType::car){
		Car.Render(Shader,GameObject::Get_ModelMatrix(),mat4(1));
	}
}

void MapObject::Set_Model()
{
	TreeModel =  Model3D();
	TreeModel.LoadFromFile("data/models/Tree/PalmTree.3ds",true);
	TreeModel.Initialize();

	
	BuildingModel =  Model3D();
	BuildingModel.LoadFromFile("data/models/house/AranHouse1_3ds.3ds",true);
	BuildingModel.Initialize();

	BuildingMode2 =  Model3D();
	BuildingMode2.LoadFromFile("data/models/house/LPBuildX12_3ds.3ds",true);
	BuildingMode2.Initialize();

	Car =  Model3D();
	Car.LoadFromFile("data/models/jeep/jeep1.3ds",true);
	Car.Initialize();

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
