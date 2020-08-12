#version 330
in vec2 passTextCoords;
in vec3 toLightVector;
in vec3 surfaceNormal;
out vec4 out_color;
uniform sampler2D textureSampler;
uniform vec3 LightColor;
void main(){
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 normalLight = normalize(toLightVector);
	float DotP = dot(unitNormal,normalLight) ;
	float brightness = max(DotP,0.0);
	vec3 diffuse = brightness*LightColor;
	out_color =vec4(diffuse,1.0)* texture(textureSampler,passTextCoords);

}