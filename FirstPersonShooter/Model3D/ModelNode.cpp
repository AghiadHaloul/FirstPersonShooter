#include "ModelNode.h"
#include <iostream>
using namespace std;

ModelNode::ModelNode(void)
{
}


ModelNode::~ModelNode(void)
{
}

void ModelNode::Render(ShaderProgram* shaderProgram, glm::mat4 parentTransforms , glm::mat4 Wheel_Rotation)
{
	glm::mat4 curTransform = parentTransforms * this->transforms;
	auto finalTrans = curTransform;
	if (name[0] == 'w')
		finalTrans = finalTrans * Wheel_Rotation;

	//glm::mat4 curTransform = parentTransforms;
	shaderProgram->BindModelMatrix(&finalTrans[0][0]);
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw();
	}
	for (int i = 0; i < children.size(); i++)
	{
		//children[i]->Render(shaderProgram, parentTransforms);
		children[i]->Render(shaderProgram, curTransform, Wheel_Rotation);
	}
}

ModelNode* ModelNode::FindNode(std::string name)
{
	// Not Tested.
	if(this->name == name)
		return this;
	ModelNode* node = 0;
	for (int i = 0; i < children.size(); i++)
	{
		if(node = children[i]->FindNode(name))
			return node;
	}
	return node;
}

std::vector<glm::vec3> ModelNode::GetVertices(glm::mat4 parentTransforms /*= (glm::mat4(1))*/)
{
	std::vector<glm::vec3> vertices;
	glm::mat4 curTransform = parentTransforms * this->transforms;

	for (int i = 0; i < meshes.size(); i++)
	{
		for (int j = 0; j < meshes[i]->VertexData.size(); j++)
		{
			glm::vec3 transformedVertex = meshes[i]->VertexData[j];
			transformedVertex = glm::vec3(curTransform * glm::vec4(transformedVertex,1));
			vertices.push_back(transformedVertex);
		}
	}
	for (int i = 0; i < children.size(); i++)
	{
		auto childVerticesTransformed = children[i]->GetVertices(curTransform);
		vertices.insert(vertices.end(),childVerticesTransformed.begin(),childVerticesTransformed.end());
	}
	return vertices;
}
