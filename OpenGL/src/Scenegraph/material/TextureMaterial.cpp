#include "TextureMaterial.h"

TextureMaterial::TextureMaterial()
	: mTextureHandler(nullptr)
{
}

TextureMaterial::~TextureMaterial()
{
}

void TextureMaterial::setTexturePath(std::string file_path)
{
	mTextureFilePath = file_path;
}

void TextureMaterial::setTextureHandler(ITextureHandlerSharedPtr texture_handler)
{
	mTextureHandler = texture_handler;
}

std::string TextureMaterial::getTexturePath()
{
	return mTextureFilePath;
}

void TextureMaterial::bindMaterialProperties()
{
	mShaderHandler->setUniformFloat("u_textureFlag",
		1.0f);
	mTextureHandler->bind(0);
}

void TextureMaterial::unbindMaterialProperties()
{
	mShaderHandler->setUniformFloat("u_textureFlag",
		0.0f);
	mTextureHandler->unbind();
}
