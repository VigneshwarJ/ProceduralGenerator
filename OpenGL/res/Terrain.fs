#version 330
in vec2 passTextCoords;
in vec3 toLightVector;
in vec3 surfaceNormal;
in vec3 toCameraVector;
out vec4 out_color;
uniform sampler2D textureSampler;
uniform vec3 LightColor;
uniform float shineDamper;
uniform float reflectivity;
void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLight = normalize(toLightVector);
	float DotP = dot(unitNormal,unitLight) ;
	float brightness = max(DotP,0.4);
	vec3 diffuse = brightness*LightColor;

    vec3 unitVectortoCam = normalize(toCameraVector);
    vec3 lightDirection = -unitLight;
    vec3 reflectDirection = reflect(lightDirection,unitNormal); 

    float specularFactor = dot(reflectDirection, unitVectortoCam);
    specularFactor = max(specularFactor,0.0);
    float dampedFactor = pow(specularFactor,shineDamper);
    vec3 finalSpecular = dampedFactor*reflectivity*LightColor;
    
	out_color =vec4(diffuse,1.0)* texture(textureSampler,passTextCoords)+vec4(finalSpecular,1.0) ;

}