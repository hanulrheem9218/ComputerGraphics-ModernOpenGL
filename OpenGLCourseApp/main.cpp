
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Mesh.h"
#include "Shader.h"


#include "Window.h"
#include "Camera.h"
#include "Texture.h"
// Window Dimensions
const float toRadians = 3.1459265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;


Window mainWindow;
Camera camera;

Texture brickTexture;
Texture dirtTexture;


// changing in time
GLfloat deltaTime;
GLfloat lastTime;
// Vertext Shader
static const char* vShader = "Shaders/shader.vert";
//Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateObject() {

	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2, 3,0,
		0,1,2
	};

	GLfloat vertices[] = {
	//   X      Y      Z     U     V
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,   0.5f, 0.0f,
		1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
		0.0f,1.0f,0.0f,		 0.5f, 1.0f
	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj2);
}


void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.initialise();
	CreateObject();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,1.0f,0.0f),-90.0f,0.0f, 5.0f, 0.5f);

	brickTexture = Texture((char*)"Textures/brick.png");
	brickTexture.LoadTexture();

	dirtTexture = Texture((char*)"Textures/dirt.png");
	dirtTexture.LoadTexture();

	

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);


	// Loop until window closed;
	while (!mainWindow.getShouldClose()) {
		// Get + handle user input events
		GLfloat now = glfwGetTime(); // SDL GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lasTime) *10000/ SDL_GetPerformanceOfFreuqency()
		lastTime = now;

		glfwPollEvents();

		// checking camera input
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		// mose control system.
		camera.mouseControl(mainWindow.getXchange(), mainWindow.getYchange());
		// clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, (curAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f,1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		meshList[1]->RenderMesh();
		// unsinged Shader.
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}