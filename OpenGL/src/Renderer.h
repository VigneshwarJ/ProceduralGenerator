#include<GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Entity.h"
#include "Light.h"
class Renderer
{
public:
	Renderer(Camera* camera,Light* light);
	void prepare();
	void render(const Entity& entity);
private:
	Shader* m_shader;
	Camera* m_camera;
	Light* m_light;
};

