#ifndef PG_OPENGLWINDOW_H
#define PG_OPENGLWINDOW_H

#include "../Scenegraph/SceneItem.h"
#include "../Camera.h"
#include "../Renderer/opengl/RenderDelegateOpenGL.h"
#include <GLFW/glfw3.h>
#include "ContextHandler.h"
#include <functional>
#include "../Events/Event.h"

class OpenGLWindow
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	OpenGLWindow(int width, int height, const std::string& Name);
	~OpenGLWindow();

	void setCamera(test::Camera* camera);
	test::Camera* getCamera();
	void initializeGL();
	void update();
	bool isClosed();
	void setScene(SceneItemSharedPtr scene);
	SceneItemSharedPtr getScene();


	void SetEventCallback(const EventCallbackFn& callback);

	//AnimationData getCurrentAnimation() const;

	//void changeCurrentAnimIndex(int index);

	//void setCurrentAnimation(const AnimationData &currentAnimation);


protected:

	void processInput();

private:

	bool mIsAnimating;
	bool mIsInitialized;
	bool mIsFirstMouseEvent;
	bool mIsCameraControlEnabled;
	bool mCloseRequested;

	float mPreviousTime;
	uint32_t mFPS;
	uint32_t mFrameCount;
	float mDeltaTime;
	int width, height;

	struct Data {
		unsigned int mWidth, mHeight;
		EventCallbackFn mEventCallback;
	};
	glm::mat4 view_matrix;
	//AnimationData mCurrentAnimation;
	ContextHandler mContextHandler;
	test::Camera* mpCamera;
	GLFWwindow* mWindow;
	Data mWindowData;
	//    LabelWidget* mpFPSLabel;
};

#endif // PG_OPENGLWINDOW_H
