#version 330 
in vec3 position;
in vec2 TextureCoords;
uniform mat4 MVP;
out vec2 passTextCoords;

void main()
{
gl_Position = MVP * vec4(position,1.0f);	
passTextCoords = TextureCoords;
}
