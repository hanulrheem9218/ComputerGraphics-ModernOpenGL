#pragma once


#include <GL/glew.h>
#include <glm/glm.hpp>


class Light
{

public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation);


	~Light();

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity;

//	glm::vec3 direction;
	GLfloat diffuseIntensity;


};

