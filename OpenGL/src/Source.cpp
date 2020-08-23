#pragma once
#include<iostream>
#include "Display.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Source.h"
#include "Loader.h"
#include "gtc/matrix_transform.hpp"
#include "Light.h"
#include "Ltrees.h"

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

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
//Camera* camera = new Camera(glm::vec3(-12.0f, -70.0f, -790.0f), 
	//glm::vec3(0.0f, 1.0f, 0.0f), 90.0f,20.0f);
Camera* camera = new Camera(glm::vec3(-36.4461, - 2.19055,  4.36589),
	glm::vec3(0.0f, 1.0f, 0.0f), 170.0f, -8.0f);
Light* light = new Light({ {2000.0f},{2000.0f},{100.0f} }, { {1.0f},{1.0f},{1.0f} });

std::vector<Entity*> entities;
std::vector<Light*> lightw;
std::vector<Terrain*> terrains;

int main(void)
{	
	srand(1000000);
	Display display(SCR_WIDTH, SCR_HEIGHT, "Procedural terrain");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	Renderer renderer;
	Mesh* mesh = Loader::loadObject("res/tree", "res/tree.png");
	
	Entity* entity = new Entity(mesh, { {0.0f}, {0.0f} ,{0.0f} }, { {0.0f}, {0.0f} ,{0.0f} }, 1.0f);

	Ltrees* ltree = new Ltrees();
	;
	//Entity* entity2 = new Entity(ltree->returnMesh(), { {0.0f}, {0.0f} ,{0.0f} }, { {0.0f}, {0.0f} ,{0.0f} }, 1.0f);
	Terrain* terrain = new Terrain(0,0, new Texture("res/grass2.png"));
	Terrain* terrain2 = new Terrain(0, 1, new Texture("res/grass2.png"));
	/*renderer.processEntities(entity);
	renderer.processTerrains(terrain);
	renderer.processTerrains(terrain2);*/
	terrains.push_back(terrain);
	terrains.push_back(terrain2);
	entities.push_back(entity);
	entities = ltree->returnEntity();
	//entities.push_back(entity2);
	renderer.renderScene(entities, light, terrains, camera);
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
		//renderer.renderScene(entities, light, terrains, camera);
			processInput(display.returnwindow());
			entity->changeRotation({ {0.0f},{0.001f},{0.0f} });
			//Display loop
			display.clear(0.52f, 0.81f, 0.95f, 1.0f);
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
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera->ProcessKeyboard(RLEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera->ProcessKeyboard(RRIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->ProcessKeyboard(RUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->ProcessKeyboard(RDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		camera->printLocation();
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