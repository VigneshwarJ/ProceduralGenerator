#include "ShaderHandlerOpenGL.h"
#include <string>
#include <fstream>
#include <iostream>



ShaderHandlerOpenGL::ShaderHandlerOpenGL()
{
	mShaderProgram = glCreateProgram();
}

ShaderHandlerOpenGL::~ShaderHandlerOpenGL()
{
}

int ShaderHandlerOpenGL::getUniformLocation(const char* uniformName)
{
	int location;
	if (uniformNameCache.find(uniformName) == uniformNameCache.end())
	{
		location = glGetUniformLocation(mShaderProgram, uniformName);
		uniformNameCache.insert({ uniformName,location });
	}
	else
	{
		location = uniformNameCache[uniformName];
	}
	if (location == -1)
		std::cout << "uniform location returned -1" << uniformName << std::endl;
	return location;
}

void ShaderHandlerOpenGL::setUniformFloat(const char* p_location,
	float value)
{
	int shader_location_ID = getUniformLocation(p_location);
	glUniform1f(shader_location_ID, value);
}

void ShaderHandlerOpenGL::setUniform2Float(const char* p_location,
	const glm::vec2& vector)
{
	int shader_location_ID = getUniformLocation(p_location);
	glUniform2f(shader_location_ID, vector[0], vector[1]);
}

void ShaderHandlerOpenGL::setUniform3Float(const char* p_location,
	const glm::vec3& vector)
{
	int shader_location_ID = getUniformLocation(p_location);
	glUniform3f(shader_location_ID, vector[0], vector[1], vector[2]);
}

void ShaderHandlerOpenGL::setUniformMatrix4x4(const char* p_location,
	const glm::mat4& matrix)
{
	int shader_location_ID = getUniformLocation(p_location);
	glUniformMatrix4fv(shader_location_ID, 1, GL_FALSE, &matrix[0][0]);

}


void ShaderHandlerOpenGL::addShaderSourceFromFile(ShaderHandlerOpenGL::ShaderType type,
	const std::string& file_path)
{
	std::ifstream file;
	file.open(file_path.c_str());
	std::string output;
	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "load the file correctly" << errno;
	}
	addShaderFromSourceCode(type, output);
}

void ShaderHandlerOpenGL::addShaderFromSourceCode(ShaderHandlerOpenGL::ShaderType type,
	const std::string& code)
{
	GLuint shader;
	shader = glCreateShader(type);
	if (shader == 0)
		std::cerr << "err in shader creation" << type << std::endl;

	const GLchar* shaderSourceString[1];
	GLint shaderSourceStrLen[1];
	shaderSourceString[0] = code.c_str();
	shaderSourceStrLen[0] = static_cast<int>(code.length());
	glShaderSource(shader, 1, shaderSourceString, shaderSourceStrLen);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR : Shader compilation failure");
	shaders.push_back(shader);

}


void ShaderHandlerOpenGL::CheckShaderError(GLuint shader, GLuint flag,
	bool isProgram, const std::string& errorMessage)
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


void ShaderHandlerOpenGL::link()
{
	for (const auto& shader : shaders)
	{
		glAttachShader(mShaderProgram, shader);
	}
	glLinkProgram(mShaderProgram);
	CheckShaderError(mShaderProgram, GL_LINK_STATUS, true, "ERROR : Program linking failed: ");
	glValidateProgram(mShaderProgram);
	CheckShaderError(mShaderProgram, GL_VALIDATE_STATUS, true, "ERROR : Program is invalid: ");
	for (const auto& shader : shaders)
	{
		glDetachShader(mShaderProgram, shader);
		glDeleteShader(shader);
	}
}

void ShaderHandlerOpenGL::bindShader()
{
	glUseProgram(mShaderProgram);
}

void ShaderHandlerOpenGL::unbindShader()
{
	glUseProgram(0);
}
