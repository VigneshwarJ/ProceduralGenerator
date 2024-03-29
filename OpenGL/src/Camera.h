#pragma once
#include "Utilities/SmartTypePtr.h"
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include <vector>
namespace test {
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		RLEFT,
		RRIGHT,
		RUP,
		RDOWN
	};
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(-53.4634, -38.8797, -23.0737),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
			float pitch = PITCH);
		~Camera();
		void move();
		glm::mat4 GetViewMatrix();
		void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
		void printLocation();

	private:
		// camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// euler Angles
		float Yaw;
		float Pitch;
		float roll;
		// camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		void updateCameraVectors();

	};
}