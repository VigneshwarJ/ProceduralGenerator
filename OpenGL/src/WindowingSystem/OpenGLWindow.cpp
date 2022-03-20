#include "OpenGLWindow.h"

#include <iostream>
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"


OpenGLWindow::OpenGLWindow(int width, int height, const std::string& name)
	: mIsAnimating(false)
	, mIsInitialized(false)
	, mIsFirstMouseEvent(true)
	, mIsCameraControlEnabled(false)
	, mCloseRequested(false)
	, mPreviousTime(0)
	, mFPS(0)
	, mFrameCount(0)
	, width(width)
	, height(height)
	, mDeltaTime(0.0f)
	, mpCamera(nullptr)
	//    , mpFPSLabel(new LabelWidget(0, 0, 300, 300))
{
	if (!glfwInit())
		return;
	mWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	mWindowData.mWidth = width;
	mWindowData.mHeight = height;
	mContextHandler.setProjectionMatrix(glm::perspective(90.0f,
		(GLfloat)width / (GLfloat)height, .10f, 150.0f));
	if (!mWindow)
	{
		glfwTerminate();
		std::cerr << "window failed to initialize\n";
		return;
	}

}

OpenGLWindow::~OpenGLWindow()
{
	glfwDestroyWindow(mWindow);
}


void OpenGLWindow::initializeGL()
{
	if (!mIsInitialized)
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(mWindow);
		//Glew initialization
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Shaader initialization failed" << std::endl;
		}
		mIsInitialized = true;

		if (mpCamera == nullptr)
		{
			std::cerr << "OpenGLWindow::initialize: "
				"No camera found, being generated automatically";
			mpCamera = new test::Camera({ 0.0f, 0.0f, 3.0f });
		}

		glfwSwapInterval(1);
		glfwSetWindowUserPointer(mWindow, &mWindowData);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
			{
				auto& data = *(Data*)glfwGetWindowUserPointer(window);
				data.mWidth = width;
				data.mHeight = height;

				WindowResizeEvent event(width, height);
				data.mEventCallback(event);
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.mEventCallback(event);
			});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.mEventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.mEventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.mEventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.mEventCallback(event);
			});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.mEventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.mEventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.mEventCallback(event);
			});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.mEventCallback(event);
			});


		view_matrix = mpCamera->GetViewMatrix();
		mContextHandler.setViewMatrix(view_matrix);
		mContextHandler.initialize();
	}
}

void OpenGLWindow::setCamera(test::Camera* camera)
{
	mpCamera = camera;
}

test::Camera* OpenGLWindow::getCamera()
{
	return mpCamera;
}

void OpenGLWindow::setScene(SceneItemSharedPtr scene)
{
	mContextHandler.setRoot(scene);
}

SceneItemSharedPtr OpenGLWindow::getScene()
{
	return mContextHandler.getSceneRoot();
}

void OpenGLWindow::SetEventCallback(const EventCallbackFn& callback)
{
	mWindowData.mEventCallback = callback;
}

void OpenGLWindow::update()
{

	float currentFrame = static_cast<float>(glfwGetTime());
	mDeltaTime = currentFrame - mPreviousTime;
	mPreviousTime = currentFrame;

	/* Swap front and back buffers */
	glfwSwapBuffers(mWindow);

	/* Poll for and process events */
	glfwPollEvents();
	GLsizei retina_scale = 1;
	processInput();
	glViewport(0,
		0,
		width * retina_scale,
		height * retina_scale);

	//check if close call is called
	mContextHandler.setViewMatrix(mpCamera->GetViewMatrix());
	mContextHandler.render(0, 0);

	++mFrameCount;
	if (glfwWindowShouldClose(mWindow))
		mCloseRequested = true;
}

bool OpenGLWindow::isClosed()
{
	return mCloseRequested;
}

void OpenGLWindow::processInput()
{
	using namespace test;
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(mWindow, true);

	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(FORWARD, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(BACKWARD, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(LEFT, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(RIGHT, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(UP, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(DOWN, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(RLEFT, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(RRIGHT, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(RUP, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		mpCamera->ProcessKeyboard(RDOWN, mDeltaTime);
	if (glfwGetKey(mWindow, GLFW_KEY_P) == GLFW_PRESS)
		mpCamera->printLocation();
}


//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    float aspect_ratio = float(width) / float(height);
//	glViewport(0, 0, width, height);
//    mContextHandler.setProjectionMatrix(glm::perspective(45.0f,
//        aspect_ratio,
//        1.0f,
//        1000.0f));
//}
//
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	mCamera->ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	mCamera->ProcessMouseScroll(yoffset);
//}