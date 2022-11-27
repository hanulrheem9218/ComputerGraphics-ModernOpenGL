
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
	//Core Profile - No Backwrads Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Comaptibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation Failed");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size Information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set Context for GLEW to use
	glfwMakeContextCurrent(mainWindow);
	//allow modern externsion features
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("GLEW initlialization Failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport Size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Loop until window closed;
	while (!glfwWindowShouldClose(mainWindow)) {
		// Get + handle user input events
		glfwPollEvents();
		
		// clear window
		glClearColor(1.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}