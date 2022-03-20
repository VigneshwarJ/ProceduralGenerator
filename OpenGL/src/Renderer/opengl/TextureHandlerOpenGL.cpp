#include "TextureHandlerOpenGL.h"
#include "../../Vendor/stb_image/stb_image.h"
#include <iostream>

TextureHandlerOpenGL::TextureHandlerOpenGL()
	: mTexture(0)
{
}

TextureHandlerOpenGL::TextureHandlerOpenGL(const std::string& filePath)
	: mTexture(0)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* m_local_buffer = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
	if (m_local_buffer == nullptr)//Error check
	{
		std::cerr << "Error when loading texture from file: " + filePath << std::endl;
	}
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (m_local_buffer)
	{
		stbi_image_free(m_local_buffer);
	}

}

TextureHandlerOpenGL::~TextureHandlerOpenGL()
{
	glDeleteTextures(1, &mTexture);
}

void TextureHandlerOpenGL::bind(unsigned int  slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

void TextureHandlerOpenGL::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
