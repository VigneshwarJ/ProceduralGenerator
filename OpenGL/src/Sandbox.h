#pragma once
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Camera.h"
class Sandbox
{
public:
	void example();
	void onEvent(Event& event);
	bool mouseMove(MouseMovedEvent& event);
private:
	bool firstMouse = true;
	double lastX = 0, lastY = 0;
	test::Camera* mpCamera = nullptr;
};

