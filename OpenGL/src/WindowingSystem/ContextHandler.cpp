#include "ContextHandler.h"


ContextHandler::ContextHandler()
	: mIsInitialized(false)
	, mSceneRoot(nullptr)
	, mRenderDelegate(RenderDelegateOpenGL())
{
}

ContextHandler::~ContextHandler()
{
}

void ContextHandler::setRoot(SceneItemSharedPtr scene)
{
	mSceneRoot = scene;
}

bool ContextHandler::isSceneValid()
{
	if (mSceneRoot)
	{
		return true;
	}

	return false;
}

SceneItemSharedPtr ContextHandler::getSceneRoot()
{
	return mSceneRoot;
}


void ContextHandler::setViewMatrix(const glm::mat4& view)
{
	mRenderDelegate.setViewMatrix(view);
}

void ContextHandler::setProjectionMatrix(const glm::mat4& projection)
{
	mRenderDelegate.setProjectionMatrix(projection);
}

void ContextHandler::initialize()
{
	mRenderDelegate.initialize();
	mRenderDelegate.commitScene(mSceneRoot);
	mIsInitialized = true;

	glm::mat4 view_matrix = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 3.0f }, glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	mRenderDelegate.setViewMatrix(view_matrix);
}

void ContextHandler::initializeContext()
{
	mRenderDelegate.commitScene(mSceneRoot);
	mIsInitialized = true;

	glm::mat4 view_matrix = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 3.0f }, glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	mRenderDelegate.setViewMatrix(view_matrix);
}

void ContextHandler::makeCurrent()
{

}

void ContextHandler::render(int animIndex, float deltaTime)
{
	mRenderDelegate.render(mSceneRoot, animIndex, deltaTime);
}

