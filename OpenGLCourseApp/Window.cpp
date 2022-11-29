#include "Window.h"

Window::Window() {
	width = 800;
	height = 600;
	xChange = 0.0f;
	yChange = 0.0f;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

int Window::initialise() {
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

 mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation Failed");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size Information

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set Context for GLEW to use
	glfwMakeContextCurrent(mainWindow);
	//allow modern externsion features

	//Handle key + mouse input
	createCallBacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		printf("GLEW initlialization Failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport Size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow,this);

}

GLfloat Window::getXchange() {
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYchange() {
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::createCallBacks() {
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		//glfwSetInputMode(theWindow->mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			printf("pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			printf("released: %d\n", key);
		}
	}

}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}
	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//printf("x:%.6f, y:%.6f\n", theWindow->xChange, theWindow->yChange);
	
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}