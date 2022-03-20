#ifndef STATICSHADERCODE_H
#define STATICSHADERCODE_H

static const char default_vertex_shader[] =
"#version 330 core\n"
"#ifdef GL_ES\n"
" precision mediump float;\n"
"#endif\n"
"layout (location=0) in vec3 a_position;\n"
"layout (location=1) in vec2 a_textureCoordinates;\n"
"layout (location=2) in vec3 a_normal;\n"
"layout (location=3) in vec4 a_vertexColor;\n"
"out vec2 v_textureCoordinates;\n"
"out vec4 v_vertexColor;\n"
"out vec3 toCameraVector;\n"
"out vec3 toLightVector;\n"
"out vec3 surfaceNormal;\n"
"uniform mat4 u_projectionMatrix;\n"
"uniform mat4 u_viewMatrix;\n"
"uniform mat4 u_modelMatrix;\n"
"uniform mat4 u_JointMatrix;\n"

"void main()\n"
"{\n"
" vec4 finalModelMat = (u_modelMatrix * u_JointMatrix) * vec4(a_position, 1.0f);"
"gl_Position = u_projectionMatrix *"
"u_viewMatrix *"
//"vec4(a_position, 1.0f);"
"finalModelMat ;"
"\n"
"v_textureCoordinates = a_textureCoordinates;\n"
"v_vertexColor = a_vertexColor;\n"
"surfaceNormal = (u_modelMatrix * vec4(a_normal,0.0f)).xyz;"
"toLightVector = vec3(0.0,2.0,0.0) - finalModelMat.xyz;\n"
"toCameraVector = (inverse(u_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - finalModelMat.xyz; \n"
"}";

static const char default_fragment_shader[] =
"#version 330 core\n"
"#ifdef GL_ES\n"
" precision mediump float;\n"
"#endif\n"
"in  vec2 v_textureCoordinates;\n"
"in vec4 v_vertexColor;\n"
"in vec3 surfaceNormal;"
"in vec3 toCameraVector; "
"in vec3 toLightVector; "
"out  vec4 fragmentColor;\n"
"uniform  sampler2D u_texture;\n"
"uniform  float u_textureFlag;\n"

"void main()\n"
"{\n"
"vec3 unitNormal = normalize(surfaceNormal);"
" vec3 unitLight = normalize(toLightVector);"
"float DotP = dot(unitNormal, unitLight);"
"float brightness = max(DotP, 0.4); "
"fragmentColor = u_textureFlag *"
"texture(u_texture, v_textureCoordinates) +"
"(1.0 - u_textureFlag) * vec4(brightness*v_vertexColor.xyz,1.0f) ;\n"
"}\n";

#endif // STATICSHADERCODE_H
