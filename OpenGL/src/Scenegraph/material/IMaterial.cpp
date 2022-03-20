#include "IMaterial.h"



IMaterial::IMaterial()
	: mShadertype(PG_DEFAULT_SHADER)
	, mShaderHandler(nullptr)
{
}

IMaterial::~IMaterial()
{
}

void IMaterial::setShaderProgramType(ShaderProgramType type)
{
	mShadertype = type;
}

void IMaterial::setShader(IShaderHandlerSharedPtr shader)
{
	mShaderHandler = shader;
}

ShaderProgramType IMaterial::getShaderProgramType()
{
	return mShadertype;
}

IShaderHandlerSharedPtr IMaterial::getShaderHandler()
{
	return mShaderHandler;
}

void IMaterial::bind()
{
	mShaderHandler->bindShader();
	bindMaterialProperties();
}

void IMaterial::unbind()
{
	unbindMaterialProperties();
	mShaderHandler->unbindShader();
}
