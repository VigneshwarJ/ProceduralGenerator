#ifndef PG_RENDERABLE_H
#define PG_RENDERABLE_H

#include "../SceneItem.h"
#include "../material/IMaterial.h"
#include "../../Renderer/IRenderableHandler.h"



enum PrimitiveType
{
	PG_TRIANGLES,
	PG_TRIANGLE_STRIP
};

MAKE_SHARED(Renderable);
class Renderable : public SceneItem
{
public:
	Renderable();
	~Renderable();

	void setMaterial(IMaterialSharedPtr material);
	void setRenderableHandler(IRenderableHandlerSharedPtr renderable_handler);

	IRenderableHandlerSharedPtr getRenderableHandler();
	IMaterialSharedPtr getMaterial();

private:
	IRenderableHandlerSharedPtr mRenderableHandler;
	IMaterialSharedPtr mMaterial;
};

#endif // PG_RENDERABLE_H
