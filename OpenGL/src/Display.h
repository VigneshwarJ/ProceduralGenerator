#include<GL/glew.h>
#include<iostream>
#include <GLFW/glfw3.h>
class Display {
public:
	Display(int WIDTH, int HEIGHT, const std::string Name);
	virtual ~Display();
	void Update();
	bool isClosed(); 
	void processInput();
	GLFWwindow* returnwindow();
	void clear(float r, float g, float b, float a);
private:
	GLFWwindow* window;
	bool m_isClosed ;

};
