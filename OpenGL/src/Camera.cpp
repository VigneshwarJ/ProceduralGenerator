#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position ,
	glm::vec3 up, float yaw ,
	float pitch )
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();

}

Camera::~Camera()
{
}
void Camera::move()
{

}
glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 Camera = glm::rotate(glm::mat4(1.0f), glm::radians(Pitch), glm::vec3(1, 0, 0));
	Camera = glm::rotate(Camera, glm::radians(Yaw), glm::vec3(0, 1, 0));
	Camera = glm::translate(Camera, Position);
	return Camera;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position[2] += 0.1 ;
	if (direction == BACKWARD)
		Position[2] -= 0.1 ;
	if (direction == LEFT)
		Position[0] += 0.1;
	if (direction == RIGHT)
		Position[0] -= 0.1;
	if (direction == UP)
		Position[1] += 0.1;
	if(direction==DOWN)
		Position[1] -= 0.1;
	if (direction == RUP)
		Pitch += PITCH;
	if (direction == RDOWN)
		Pitch -= PITCH ;
	if (direction == RLEFT)
		Yaw += YAW;
	if (direction == RRIGHT)
		Yaw -= YAW ;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::printLocation()
{
	std::cout << Position[0] << "  " << Position[1] << "  " << Position[2] << std::endl;
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}



