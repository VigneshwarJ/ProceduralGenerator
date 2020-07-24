#include "Texture.h"
#include "Vender/stb_image/stb_image.h"
#include <iostream>
Texture::Texture(const std::string& filePath) :
	m_FileName(filePath),m_Texture_ID(0),m_local_buffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
	
	stbi_set_flip_vertically_on_load(0);
	m_local_buffer = stbi_load(filePath.c_str(),&m_Width,&m_Height,&m_BPP,4);
	if (m_local_buffer == nullptr)//Error check
	{
		std::cerr << "Error when loading texture from file: " + filePath << std::endl;
	}
	glGenTextures(1, &m_Texture_ID);
	glBindTexture(GL_TEXTURE_2D, m_Texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (m_local_buffer)
	{
		stbi_image_free(m_local_buffer);
	}

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture_ID);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Texture_ID);

}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
