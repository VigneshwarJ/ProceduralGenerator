#include "Loader.h"
#include <sstream>

Loader::Loader()
{
}

Loader::~Loader()
{
}
Mesh* Loader::loadObject(const std::string& fileName,const std::string& textureName)
{
	std::ifstream file;
	std::string output;
	std::string line;
	std::string token;
	//std::string word;
	file.open((fileName + ".obj").c_str());
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textures;
	std::vector<unsigned int> indeces;
	glm::vec3* normals_final = nullptr;
	glm::vec2* textures_final = nullptr;
	bool first = true;
	float pos1, pos2, pos3;
	int index;
	int i;
	Texture* texture = nullptr;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			std::string word;
			std::istringstream tokenStream(line);
			std::getline(tokenStream, word, ' ');
			if (line[0] == 'v' && line[1] == ' ')
			{
				std::getline(tokenStream, word, ' ');
				pos1 = std::stof(word);
				std::getline(tokenStream, word, ' ');
				pos2 = std::stof(word);
				std::getline(tokenStream, word, ' ');
				pos3 = std::stof(word);
				//std::cout << pos1 << " "<<pos2 << " "  << pos3 << std::endl;
				vertices.push_back(glm::vec3(pos1, pos2, pos3));

			}
			else if (line[0] == 'v' && line[1] == 't')
			{
				std::getline(tokenStream, word, ' ');
				pos1 = std::stof(word);
				std::getline(tokenStream, word, ' ');
				pos2 = std::stof(word);
				textures.push_back(glm::vec2(pos1, pos2));
			}
			else if (line[0] == 'v' && line[1] == 'n')
			{
				std::getline(tokenStream, word, ' ');
				pos1 = std::stof(word);
				std::getline(tokenStream, word, ' ');
				pos2 = std::stof(word);
				std::getline(tokenStream, word, ' ');
				pos3 = std::stof(word);
				normals.push_back(glm::vec3(pos1, pos2, pos3));
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{
				if (first) {
					//std::cout << vertices.size() << "  " << normals.size() << " " << textures.size();
					normals_final = new glm::vec3[vertices.size()];
					textures_final = new glm::vec2[vertices.size()];
					i = 0;
					first = false;
				}
				for (size_t x = 0; x < 3; x++)
				{
					std::getline(tokenStream, word, ' ');
					std::istringstream wordStream(word);
					wordStream >> i;
					i--;
					indeces.push_back(i);
					char temp;
					wordStream >> temp >> index; index--;
					textures_final[i] = textures[index];
					wordStream >> temp >> index; index--;
					normals_final[i] = normals[index];
				}
			}
		}
		if (&textureName != nullptr)
		{
			texture = new Texture(textureName);
		}
		Mesh* mesh = new Mesh(&vertices[0][0], &indeces[0], (float*)textures_final, (float*)normals_final,
			(unsigned int)vertices.size(), (unsigned int)indeces.size(), 
			(unsigned int)vertices.size(), (unsigned int)vertices.size(),texture);
		return mesh;
	}
	else {
		std::cout << "load the file correctly" << errno;
	}
	return nullptr;
}
