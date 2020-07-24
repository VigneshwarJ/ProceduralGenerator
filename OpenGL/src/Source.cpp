#include<iostream>
#include "Display.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Source.h"

int main(void)
{	
	Display display(800, 600, "Useless");
	Renderer renderer;
	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5,-0.5,0)),
		Vertex(glm::vec3(-0.5, 0.5,0)),
		Vertex(glm::vec3( 0.5,-0.5,0)),
		Vertex(glm::vec3(0.5,0.5,0))		
	};
	glm::vec2 textCoord[] = {
		glm::vec2(0,1),
		glm::vec2(0,0),
		glm::vec2(1,1),
		glm::vec2(1,0)
	};
	unsigned int indeces[] = {
		0,1,2,
		2,3,1
	};
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	Mesh mesh(vertices,indeces, sizeof(vertices) / sizeof(vertices[0]),sizeof(indeces)/sizeof(indeces[0]), textCoord, sizeof(textCoord)/sizeof(textCoord[0]));
	//Display loop
	while (!display.isClosed())
	{
		display.clear(0.12f, 0.21f, 0.15f, 1.0f);
		renderer.render(mesh);
		display.Update();
	}
	return 0;
}