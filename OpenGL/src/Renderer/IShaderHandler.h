#ifndef PG_ISHADERHANDLER_H
#define PG_ISHADERHANDLER_H


#include "../utilities/SmartTypePtr.h"


enum ShaderProgramType
{
	PG_DEFAULT_SHADER
};

MAKE_SHARED(IShaderHandler);
class IShaderHandler
{
public:
	enum ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};
	IShaderHandler();
	virtual ~IShaderHandler();

	virtual void setUniformFloat(const char* p_location,
		float value) = 0;
	virtual void setUniform2Float(const char* p_location,
		const glm::vec2& value) = 0;
	virtual void setUniform3Float(const char* p_location,
		const glm::vec3& value) = 0;
	virtual void setUniformMatrix4x4(const char* p_location,
		const glm::mat4& matrix) = 0;

	virtual void bindShader() = 0;
	virtual void unbindShader() = 0;
};

#endif // PG_ISHADERHANDLER_H
