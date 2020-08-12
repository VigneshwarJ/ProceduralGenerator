#version 330 
in vec3 position;
in vec2 TextureCoords;
in vec3 normals;
out vec2 passTextCoords;
out vec3 toLightVector;
out vec3 surfaceNormal;
uniform mat4 TransformationMat;
uniform mat4 ViewMat;
uniform mat4 ProjectionMat;
uniform vec3 lightPosition;

void main()
{
vec4 worldPosition = TransformationMat * vec4(position,1.0f);
gl_Position = ProjectionMat * ViewMat * worldPosition;	
passTextCoords = TextureCoords;
surfaceNormal = (TransformationMat * vec4(normals,0.0f)).xyz;
toLightVector = lightPosition - worldPosition.xyz;
}
