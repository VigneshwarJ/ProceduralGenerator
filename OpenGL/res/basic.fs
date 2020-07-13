#version 330
in vec3 acolor;

void main(){
	gl_FragColor = vec4(acolor, 1.0f);
}