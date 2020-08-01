#include<iostream>
#include "Display.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Source.h"
#include "gtc/matrix_transform.hpp"

int main(void)
{	
	Display display(800, 600, "Useless");
	Renderer renderer;
	glm::vec3 vertices[] = {
		glm::vec3(-0.5,-0.5,-1),
		glm::vec3(-0.5, 0.5,-1),
		glm::vec3( 0.5,-0.5,-1),
		glm::vec3(0.5,0.5,-1)		
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
	
	

	unsigned int noVertices = sizeof(vertices) / sizeof(vertices[0]);
	unsigned int noIndeces = sizeof(indeces) / sizeof(indeces[0]);
	unsigned int noTextCoord = sizeof(textCoord) / sizeof(textCoord[0]);
	std::cout << sizeof(vertices[0]) << " " << sizeof(vertices);
	Mesh mesh((float*)vertices,indeces, noVertices, noIndeces,(float*) textCoord, noTextCoord);
	//Display loop
	while (!display.isClosed())
	{
		display.clear(0.12f, 0.21f, 0.15f, 1.0f);
		renderer.render(mesh);
		display.Update();
	}
	return 0;
}