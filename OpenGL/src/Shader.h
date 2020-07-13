#include<gl/glew.h>
#include <string>
class Shader {
public:
	Shader(const std::string& filename);
	void bind();
	virtual ~Shader();
private:
	static const unsigned int NO_SHADERS = 2;
	GLuint m_program;
	GLuint m_shader[NO_SHADERS];
	GLuint createShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
};