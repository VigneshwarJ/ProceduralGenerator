#include "Renderable.h"



Renderable::Renderable()
	: mRenderableHandler(nullptr)
	, mMaterial(nullptr)
{
}

Renderable::~Renderable()
{
}

void Renderable::setMaterial(IMaterialSharedPtr material)
{
	mMaterial = material;
}

void Renderable::setRenderableHandler(
	IRenderableHandlerSharedPtr renderable_handler)
{
	mRenderableHandler = renderable_handler;
}

IRenderableHandlerSharedPtr Renderable::getRenderableHandler()
{
	return mRenderableHandler;
}

IMaterialSharedPtr Renderable::getMaterial()
{
	return mMaterial;
}
