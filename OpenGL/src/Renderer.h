#include<GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
class Renderer
{
public:
	Renderer();
	void prepare();
	void render(const Mesh& mesh);
private:
	Shader* m_shader;
	Camera* m_camera;
};

