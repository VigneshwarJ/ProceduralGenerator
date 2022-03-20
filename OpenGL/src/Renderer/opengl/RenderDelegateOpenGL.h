#ifndef PG_RENDERDELEGATEOPENGL_H
#define PG_RENDERDELEGATEOPENGL_H

#include "RendererOpenGL.h"
#include "SceneSettingsOpenGL.h"



class RenderDelegateOpenGL
{
public:
	RenderDelegateOpenGL();
	~RenderDelegateOpenGL();

	void setViewMatrix(const glm::mat4& matrix);
	void setProjectionMatrix(const glm::mat4& matrix);
	void initialize();
	void commitScene(SceneItemSharedPtr scene);
	void render(SceneItemSharedPtr scene, int AnimIndex, float deltatime);

private:
	enum TraversalState
	{
		PG_COMMIT,
		PG_RENDER
	};

	void sceneGraphTraversal(SceneItemSharedPtr node, TraversalState);


	RendererOpenGL mRenderer;
	ShaderProgramType mShaderProgramType;
	SceneSettingsOpenGL mSceneSettings;
	float mDeltaTime = 0;
	int mIndex = 0;
};


#endif // PG_RENDERDELEGATEOPENGL_H
