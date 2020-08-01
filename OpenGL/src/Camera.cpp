#include "Camera.h"

Camera::Camera():
    View(glm::mat4(1))
{

}

Camera::~Camera()
{
}

glm::mat4 Camera::viewMat()
{
    View = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
	return View;
}
