#ifndef PG_CONTEXTHANDLER_H
#define PG_CONTEXTHANDLER_H

#include "../Renderer/opengl/RenderDelegateOpenGL.h"

class ContextHandler
{
public:
	ContextHandler();
	~ContextHandler();

	void initialize();
	void initializeContext();
	void makeCurrent();
	void setRoot(SceneItemSharedPtr scene);
	bool isSceneValid();

	SceneItemSharedPtr getSceneRoot();
	void setViewMatrix(const glm::mat4& view);
	void setProjectionMatrix(const glm::mat4& projection);
	void render(int animIndex, float deltaTime);

private:
	bool mIsInitialized;
	SceneItemSharedPtr mSceneRoot;
	RenderDelegateOpenGL mRenderDelegate;
};

#endif // PG_CONTEXTHANDLER_H
