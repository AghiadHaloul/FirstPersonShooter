#include "TexturedModel.h"


TexturedModel::TexturedModel(void)
{
}

TexturedModel::TexturedModel(string TexturePath,int TextUnit)
{
	texture = new Texture(TexturePath, TextUnit);
}


TexturedModel::~TexturedModel(void)
{
}

void TexturedModel::Draw()
{
	texture->Bind();
	Model::Draw();
}