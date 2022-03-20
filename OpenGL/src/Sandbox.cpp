#include "Sandbox.h"
#include "WindowingSystem/OpenGLWindow.h"
#include "Procedural/Terrain.h"
#include <array>
#include "Scenegraph/geometry/PolygonalGeometry.h"
#include "Scenegraph/material/DiffuseMaterial.h"
#include <iostream>
#include "Events/MouseEvent.h"
#include "Procedural/Ltrees.h"






void Sandbox::example() {

	OpenGLWindow window(800, 600, "Procedural terrain");
	mpCamera = new test::Camera();
	Terrain* terrain = new Terrain(0, 0);
	Terrain* terrain2 = new Terrain(0, 1);
	Ltrees tree(4);
	SceneItemSharedPtr root = std::make_shared<SceneItem>();

	//root->setScale(1.f, 1.f);
	root->addChild(terrain->proceduralTerrain());
	root->addChild(terrain2->proceduralTerrain());
	root->addChild(tree.returnMesh());

	window.setScene(root);
	window.setCamera(mpCamera);
	window.SetEventCallback(std::bind(&Sandbox::onEvent, this, std::placeholders::_1));
	window.initializeGL();
	while (!window.isClosed())
	{
		window.update();
	}
}

void Sandbox::onEvent(Event& event)
{
	if (event.GetEventType() == EventType::WindowClose)
	{

	}
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Sandbox::mouseMove));

}

bool Sandbox::mouseMove(MouseMovedEvent& event)
{
	double xpos = event.GetX();
	double ypos = event.GetY();
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = static_cast<float>(xpos - lastX);
	float yoffset = static_cast<float>(lastY -ypos); // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	mpCamera->ProcessMouseMovement(xoffset, yoffset);

	return false;
}


int main()
{
	Sandbox h;
	h.example();

}