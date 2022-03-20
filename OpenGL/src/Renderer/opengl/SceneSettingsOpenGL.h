#ifndef PG_SCENESETTINGSOPENGL_H
#define PG_SCENESETTINGSOPENGL_H

#include "../ISceneSettings.h"
#include "ShaderHandlerOpenGL.h"



MAKE_SHARED(SceneSettingsOpenGL);
class SceneSettingsOpenGL : public ISceneSettings
{
public:
    SceneSettingsOpenGL();
    ~SceneSettingsOpenGL() override;

    void setViewMatrix(const glm::mat4 matrix) override;
    void setProjectionMatrix(const glm::mat4 matrix) override;
    void setModelMatrix(const glm::mat4 matrix) override;
    void setJointMatrix(const glm::mat4 matrix) override;
    void setShaderHandler(ShaderHandlerOpenGLSharedPtr handler);

    void applyViewMatrix();
    void applyProjectionMatrix();
    void applyModelMatrix();
    void applyJointMatrix();

private:
    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mModelMatrix;
    glm::mat4 mJointMatrix;
    ShaderHandlerOpenGLSharedPtr mShaderHandler;
};


 // namespace PG
#endif // PG_SCENESETTINGSOPENGL_H
