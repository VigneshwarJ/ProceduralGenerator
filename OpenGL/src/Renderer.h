#include<GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
class Renderer
{
public:
	Renderer();
	void prepare();
	void render(const Mesh& mesh);
private:
	Shader* m_shader;
};

