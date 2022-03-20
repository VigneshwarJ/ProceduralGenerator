#ifndef PG_TEXTUREHANDLEROPENGL_H
#define PG_TEXTUREHANDLEROPENGL_H


#include "../../utilities/SmartTypePtr.h"
#include "../ITextureHandler.h"


MAKE_SHARED(TextureHandlerOpenGL);
class TextureHandlerOpenGL : public ITextureHandler
{
public:
	TextureHandlerOpenGL();
	TextureHandlerOpenGL(const std::string& file_path);
	~TextureHandlerOpenGL() override;

	void bind(unsigned int  slot) override;
	void unbind() override;

private:
	GLuint mTexture;
};

#endif // PG_TEXTUREHANDLEROPENGL_H
