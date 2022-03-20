#ifndef PG_IMATERIAL_H
#define PG_IMATERIAL_H

#include "../../utilities/SmartTypePtr.h"
#include "../SceneItem.h"
#include "../../Renderer/IShaderHandler.h"


MAKE_SHARED(IMaterial);
class IMaterial : public SceneItem
{
public:
	IMaterial();
	virtual ~IMaterial();

	void setShaderProgramType(ShaderProgramType type);
	void setShader(IShaderHandlerSharedPtr shader);

	ShaderProgramType getShaderProgramType();
	IShaderHandlerSharedPtr getShaderHandler();

	void bind();
	void unbind();

protected:
	virtual void bindMaterialProperties() = 0;
	virtual void unbindMaterialProperties() = 0;

	ShaderProgramType mShadertype;
	IShaderHandlerSharedPtr mShaderHandler;
};
#endif // PG_IMATERIAL_H
