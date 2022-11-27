
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Window Dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main() 
{
	//Initialize GLFW
	if (!glfwInit()) {
		printf("GLFW Initialization failed!");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW window Properties
	//OpenGl Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return 0;
}