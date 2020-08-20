#pragma once
#include "Vertex.h"
#include "Vender/stb_image/stb_image.h"
#include <string>
class Texture
{
private: 
	unsigned int m_Texture_ID;
	std::string m_FileName;
	unsigned char* m_local_buffer;
	int m_Width, m_Height, m_BPP;
	float Shinedamper;
	float reflectivity;
public:
	Texture(const std::string& filePath);
	~Texture();
	void setReflectivity(float ref);
	void setShineDampner(float shine);
	float returnShineDampner();
	float returnReflectivity();

	void bind(unsigned int slot = 0) const;
	void unbind() const;



};

