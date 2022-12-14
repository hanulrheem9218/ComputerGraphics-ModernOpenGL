#include "Camera.h"

Camera::Camera(){}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovespeed, GLfloat startTurnspeed) {
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMovespeed;
	turnSpeed = startTurnspeed;

	update();
}
void Camera::keyControl(bool* keys, GLfloat deltaTime) {
	
	GLfloat velocity = moveSpeed * deltaTime;
	bool shiftKey = keys[GLFW_KEY_LEFT_SHIFT];
	GLfloat accerlation = 2;
	
	if (keys[GLFW_KEY_W]) {
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S]) {
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A]) {
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D]) {
		position += right * velocity;
	}
	// shift keys
	if (keys[GLFW_KEY_W] && shiftKey) {
		position += front * velocity * accerlation;
	}
	if (keys[GLFW_KEY_S] && shiftKey) {
		position -= front * velocity * accerlation;
	}
	if (keys[GLFW_KEY_A] && shiftKey) {
		position -= right * velocity * accerlation;
	}
	if (keys[GLFW_KEY_D] && shiftKey) {
		position += right * velocity * accerlation;
	}

}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	update();
}


glm::mat4 Camera::calculateViewMatrix() {
	//camera looking at posistion
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraDirection() {
	return glm::normalize(front);
}

glm::vec3 Camera::getCameraPosition() {
	return position;
}

void Camera::update() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	// normalizing value deleting magnitutde
	front = glm::normalize(front);
	// still dont know whats croos means
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera() {

}