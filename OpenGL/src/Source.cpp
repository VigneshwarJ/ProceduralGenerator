#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"

int main(void)
{	
	Display display(800, 600, "Useless");
	Shader shader("res/basic");
	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5,-0.5,0)),
		Vertex(glm::vec3(-0.5, 0.5,0)),
		Vertex(glm::vec3( 0.5,-0.5,0)),
		Vertex(glm::vec3(-0.5, 0.5,0)),
		Vertex(glm::vec3(0.5,0.5,0)),
		Vertex(glm::vec3(0.5,-0.5,0))
		
	};
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	//Display loop
	while (!display.isClosed())
	{
		display.clear(0.12f, 0.21f, 0.15f, 1.0f);
		shader.bind();
		mesh.draw();
		display.Update();
	}
	return 0;
}