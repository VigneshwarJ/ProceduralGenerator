#include "Shader.h"
#include <fstream>
#include <iostream>
static std::string LoadShader(const std::string& filename);

Shader::Shader(const std::string& filename) {

	m_program = glCreateProgram();
	/* Shader creation */
	m_shader[0] = createShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	m_shader[1] = createShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);
	/* Shader binding */
	for (int i = 0; i < NO_SHADERS; i++)
	{
		glAttachShader(m_program, m_shader[i]);
	}
	glBindAttribLocation(m_program, 0, "position");
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR : Program linking failed: ");
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "ERROR : Program is invalid: ");
}
Shader::~Shader()
{
	for (int i = 0; i < NO_SHADERS; i++)
	{
		glDetachShader(m_program, m_shader[i]);
		glDeleteShader(m_shader[i]);
	}
	glDeleteProgram(m_program);
}

void Shader::bind()
{
	glUseProgram(m_program);
}
GLuint Shader::createShader(const std::string& text, GLenum shaderType) {
	GLuint shader;
	shader = glCreateShader(shaderType);
	if (shader == 0)
		std::cerr << "err in shader creation" << std::endl;

	const GLchar* shaderSourceString[1];
	GLint shaderSourceStrLen[1];
	shaderSourceString[0] = text.c_str();
	shaderSourceStrLen[0] = text.length();
	glShaderSource(shader, 1, shaderSourceString, shaderSourceStrLen);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR : Shader compilation failure");
	return shader;
	//gl;
}

static std::string LoadShader(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str());
	std::string output;
	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
			/*std::cout << line << std::endl;*/
		}
	}
	else {
		std::cerr << "load the file correctly" << errno;
	}
	return output;
}
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}