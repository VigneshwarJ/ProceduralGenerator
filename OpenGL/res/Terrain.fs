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
float blend;
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
    float backtexAmount = 1-unitNormal.g;
    vec2 tiled_texture = passTextCoords * 40.0f;
    vec4 defaultTexture = texture(textureSampler,tiled_texture);
    vec4 rtext_color = texture(RSampler,tiled_texture);
    vec4 gtext_color = texture(GSampler,tiled_texture);
    vec4 btext_color = texture(BSampler,tiled_texture);
    vec4 total_color;
    if(backtexAmount < 0.2)
    {
        blend = unitNormal.g;
        //blend = max(blend,0.0);
        total_color =mix(rtext_color,gtext_color,blend);
        //total_color = vec4(blend,0.0,0.0,1.0);
    }
    if(backtexAmount >= 0.2 && (backtexAmount < 0.7))
    {
        blend = (unitNormal.g-.2f) / (0.7f - 0.2f);
        total_color =  mix(btext_color,gtext_color,blend);
        //total_color = vec4(0.0,blend,0.0,1.0);
    }
    if(backtexAmount >= 0.7)
    {
        total_color = btext_color;
        //total_color = vec4(0.0,0.0,1.0,1.0);
    }
	out_color =vec4(diffuse,1.0)* total_color;

}