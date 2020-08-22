#version 330
in vec2 passTextCoords;
in vec3 toLightVector;
in vec3 surfaceNormal;
in vec3 toCameraVector;
out vec4 out_color;
uniform sampler2D textureSampler;
uniform sampler2D RSampler;
uniform sampler2D GSampler;
uniform sampler2D BSampler;
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
    //vec4 blendMap_color = texture(textureSampler,passTextCoords);
    float backtexAmount = 1-(unitNormal.r + unitNormal.g + unitNormal.b);
    vec2 tiled_texture = passTextCoords * 40.0f;
    vec4 defaultTexture = texture(textureSampler,tiled_texture)*backtexAmount;
    vec4 rtext_color = texture(RSampler,tiled_texture)*unitNormal.r;
    vec4 gtext_color = texture(GSampler,tiled_texture)*unitNormal.g;
    vec4 btext_color = texture(BSampler,tiled_texture)*unitNormal.b;
    vec4 total_color =  rtext_color + gtext_color + btext_color;
    if(total_color.a < 0.5)
    {
        total_color = defaultTexture;
    }
	out_color =vec4(diffuse,1.0)* total_color;

}