#version 330 
attribute vec3 position;
out vec3 acolor;

void main()
{
gl_Position = vec4(position,1.0f);	
acolor = position + vec3(0.5,0.5,0.5);
}
