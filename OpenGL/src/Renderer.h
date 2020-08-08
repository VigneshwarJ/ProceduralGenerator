#include<GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Entity.h"
class Renderer
{
public:
	Renderer(Camera* camera);
	void prepare();
	void render(const Entity& entity);
private:
	Shader* m_shader;
	Camera* m_camera;
};

