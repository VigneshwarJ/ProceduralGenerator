#pragma once
#include<iostream>
#include "Display.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Source.h"
#include "Loader.h"
#include "gtc/matrix_transform.hpp"
#include "Light.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset );
int main(void);
void processInput(GLFWwindow* window);
Camera* camera = new Camera(glm::vec3(0.0f, 2.0f, 5.0f), 
	glm::vec3(0.0f, 1.0f, 0.0f), -90.0f,-20);
Light* light = new Light({ {1000.0f},{1000.0f},{-3000.0f} }, { {1.0f},{1.0f},{1.0f} });

int main(void)
{	

	Display display(SCR_WIDTH, SCR_HEIGHT, "Procedural terrain");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	Renderer renderer;
	Mesh* mesh = Loader::loadObject("res/tree", "res/tree.png");
	//Mesh* mesh2 = Loader::loadObject("res/batwing", "res/tree.png");
	Mesh* mesh3 = Loader::loadObject("res/cube", "res/tree.png");
	Mesh* mesh4 = Loader::loadObject("res/cube", "res/tree.png");
	Mesh* mesh5 = Loader::loadObject("res/cube", "res/tree.png");
	Mesh* mesh6 = Loader::loadObject("res/cube", "res/tree.png");
	Mesh* mesh7 = Loader::loadObject("res/cube", "res/tree.png");
	Mesh* mesh8 = Loader::loadObject("res/cube", "res/tree.png");
	
	Entity* entity = new Entity(mesh, { {0.0f}, {0.0f} ,{0.0f} }, { {0.0f}, {0.0f} ,{0.0f} }, 0.5f);
	Entity* entity2 = new Entity(mesh4, { {1.0f}, {0.0f} ,{0.0f} }, { {90.0f}, {0.0f} ,{90.0f} }, 0.005f);
	Entity* entity3 = new Entity(mesh3, { {-1.0f}, {0.0f} ,{0.0f} }, { {0.0f}, {0.0f} ,{0.0f} }, 0.5f);
	Entity* entity4 = new Entity(mesh5, { {1.0f}, {0.0f} ,{0.0f} }, { {90.0f}, {0.0f} ,{90.0f} }, 0.005f);
	Entity* entity5 = new Entity(mesh6, { {1.5f}, {0.0f} ,{0.0f} }, { {0.0f}, {0.0f} ,{0.0f} }, 0.25f);
	Entity* entity6 = new Entity(mesh7, { {1.0f}, {0.0f} ,{0.0f} }, { {90.0f}, {0.0f} ,{90.0f} }, 0.005f);
	Entity* entity7 = new Entity(mesh8, { {-1.5f}, {0.0f} ,{0.0f} }, { {0.0f}, {0.0f} ,{0.0f} }, 0.25f);

	Terrain* terrain = new Terrain(0,-1, new Texture("res/grass.png"));
	Terrain* terrain2 = new Terrain(-1, -1, new Texture("res/grass.png"));
	renderer.processEntities(entity);
	renderer.processEntities(entity2);
	renderer.processEntities(entity3);
	renderer.processEntities(entity4);
	renderer.processEntities(entity5);
	renderer.processEntities(entity6);
	renderer.processEntities(entity7);
	renderer.processTerrains(terrain);
	renderer.processTerrains(terrain2);
	/*glfwSetCursorPosCallback(display.returnwindow(), mouse_callback);
	glfwSetScrollCallback(display.returnwindow(), scroll_callback);*/
	//Display loop
	while (!display.isClosed())
	{
		//input handling
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		processInput(display.returnwindow());
		entity->changeRotation({ {0.0f},{0.001f},{0.0f} });
		//Display loop
		display.clear(0.12f, 0.21f, 0.15f, 1.0f);
		renderer.render(light, camera);
		display.Update();
	}
	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}