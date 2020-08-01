cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)

add_executable(Procedural_Terrain 
	OpenGL/src/Camera.cpp  
	OpenGL/src/Display.cpp  
	OpenGL/src/IndexBuffer.cpp  
	OpenGL/src/Loader.cpp
	OpenGL/src/Mesh.cpp  
	OpenGL/src/Source.cpp  
	OpenGL/src/Renderer.cpp  
	OpenGL/src/Shader.cpp  
	OpenGL/src/Texture.cpp  
	OpenGL/src/VertexArray.cpp  
	OpenGL/src/VertexBuffer.cpp  
	OpenGL/src/Vender/stb_image/stb_image.cpp
	)

include_directories(
    Dependencies/GLEW/include/
    Dependencies/GLFW/include/
    Dependencies/glm/
    src/
    src/Vendor/stb_image/
)

#add_library(STB_IMAGE "OpenGL/src/Vender/stb_image/stb_image.cpp")
set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
	#	STB_IMAGE 
)
target_link_libraries(Procedural_Terrain
	${ALL_LIBS}
)

