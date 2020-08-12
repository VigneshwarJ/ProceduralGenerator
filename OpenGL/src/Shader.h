#include "Vertex.h"
#include <string>
#include <unordered_map>
class Shader {
public:
	Shader(const std::string& filename);
	void bind() const;
	void unbind() const;
	void setUniformLocation4f(const std::string& uniformName,glm::vec4 vector);
	void setUniformLocation3f(const std::string& uniformName, glm::vec3 vector);
	void setUniformLocation1i(const std::string& uniformName, int vector);

	void setUniformLocationMat4(const std::string& uniformName, const glm::mat4& MVP);

	virtual ~Shader();
private:
	static const unsigned int NO_SHADERS = 2;
	GLuint m_program;
	GLuint m_shader[NO_SHADERS];
	GLuint createShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	int getUniformLocation(const std::string& uniformName);
	std::unordered_map<std::string,int>  uniformNameCache;
};