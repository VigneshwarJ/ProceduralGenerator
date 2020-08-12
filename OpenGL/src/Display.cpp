#include "Display.h"
Display::Display(int WIDTH, int HEIGHT, const std::string Name ):
	window(nullptr),m_isClosed(false)
{
	/* Initialize the library */
	if (!glfwInit())
		return ;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, Name.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	//Glew initialization
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Shaader initialization failed" << std::endl;
	}
	m_isClosed = false;
}
void Display::Update() {
	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	

		//check if close call is called
		if (glfwWindowShouldClose(window))
		m_isClosed = true;
}
bool Display::isClosed()
{
	return m_isClosed;
}
GLFWwindow* Display::returnwindow()
{
	return window;
}
Display::~Display()
{
	glfwTerminate();
}
void Display::clear(float r, float g, float b, float a)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}