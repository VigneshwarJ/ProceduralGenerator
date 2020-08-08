#version 330
in vec2 passTextCoords;
out vec4 out_color;
uniform sampler2D textureSampler;
void main(){
	out_color = texture(textureSampler,passTextCoords);

}