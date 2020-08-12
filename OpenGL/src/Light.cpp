#include "Light.h"

Light::Light(glm::vec3 position,glm::vec3 color) :
	position(position),color(color)
{

}

glm::vec3 Light::getPosition()
{
	return position;
}

glm::vec3 Light::getColor()
{
	return color;
}
