#ifndef PG_SHADERHANDLEROPENGL_H
#define PG_SHADERHANDLEROPENGL_H

#include "../IShaderHandler.h"
#include <unordered_map>


MAKE_SHARED(ShaderHandlerOpenGL);
class ShaderHandlerOpenGL : public IShaderHandler
{
public:


    ShaderHandlerOpenGL();
    ~ShaderHandlerOpenGL() override;

    void setUniformFloat(const char *p_location,
                         float value) override;
    void setUniform2Float(const char *p_location,
                          const glm::vec2 &value) override;
    void setUniform3Float(const char *p_location,
                          const glm::vec3 &value) override;
    void setUniformMatrix4x4(const char *p_location,
                             const glm::mat4 &matrix) override;
    void addShaderSourceFromFile(ShaderHandlerOpenGL::ShaderType type,
                                 const std::string& file_path);
    void addShaderFromSourceCode(ShaderHandlerOpenGL::ShaderType type,
                                    const std::string& code);

    void link();
    void bindShader() override;
    void unbindShader() override;

private:
    GLuint mShaderProgram;
    std::vector<GLuint> shaders;
    std::unordered_map<std::string, int>  uniformNameCache;
    int getUniformLocation(const char* uniformName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

};

#endif // PG_SHADERHANDLEROPENGL_H
