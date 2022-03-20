#include "SceneSettingsOpenGL.h"
#include <iostream>


SceneSettingsOpenGL::SceneSettingsOpenGL()
    : mShaderHandler(nullptr)
{
}

SceneSettingsOpenGL::~SceneSettingsOpenGL()
{
}

void SceneSettingsOpenGL::setViewMatrix(const glm::mat4 matrix)
{
    mViewMatrix = matrix;
}

void SceneSettingsOpenGL::setProjectionMatrix(const glm::mat4 matrix)
{
    mProjectionMatrix = matrix;
}

void SceneSettingsOpenGL::setModelMatrix(const glm::mat4 matrix)
{
    mModelMatrix = matrix;
}

void SceneSettingsOpenGL::setJointMatrix(const glm::mat4 matrix)
{
    mJointMatrix = matrix;
}

void SceneSettingsOpenGL::setShaderHandler(ShaderHandlerOpenGLSharedPtr handler)
{
    mShaderHandler = handler;
}

void SceneSettingsOpenGL::applyViewMatrix()
{
    if (mShaderHandler)
    {
        mShaderHandler->setUniformMatrix4x4("u_viewMatrix",
                                             mViewMatrix);
    }
    else
    {
        // TODO: Raise a warning saying shader handler not found
    }
}

void SceneSettingsOpenGL::applyProjectionMatrix()
{
    if (mShaderHandler)
    {
        mShaderHandler->setUniformMatrix4x4("u_projectionMatrix",
                                             mProjectionMatrix);
    }
    else
    {
        // TODO: Raise a warning saying shader handler not found
    }
}

void SceneSettingsOpenGL::applyModelMatrix()
{
    if (mShaderHandler)
    {
        mShaderHandler->setUniformMatrix4x4("u_modelMatrix",
                                             mModelMatrix);
    }
    else
    {
        // TODO: Raise a warning saying shader handler not found
    }
}

void SceneSettingsOpenGL::applyJointMatrix()
{
    if (mShaderHandler)
    {
        mShaderHandler->setUniformMatrix4x4("u_JointMatrix",
                                             mJointMatrix);
    }
    else
    {
        std::cerr<<"error applyJointMatrix\n";
        // TODO: Raise a warning saying shader handler not found
    }
}
