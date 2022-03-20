#ifndef PG_TEXTUREMATERIAL_H
#define PG_TEXTUREMATERIAL_H

#include "IMaterial.h"
#include "../../Renderer/ITextureHandler.h"



MAKE_SHARED(TextureMaterial);
class TextureMaterial : public IMaterial
{
public:
	TextureMaterial();
	~TextureMaterial() override;

	void setTexturePath(std::string file_path);
	void setTextureHandler(ITextureHandlerSharedPtr texture_handler);

	std::string getTexturePath();

protected:
	void bindMaterialProperties() override;
	void unbindMaterialProperties() override;

private:
	std::string mTextureFilePath;
	ITextureHandlerSharedPtr mTextureHandler;
};

#endif // PG_TEXTUREMATERIAL_H
