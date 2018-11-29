#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <iostream>
#include <glew\glew.h>
#include <glm\glm.hpp>
#include <stdio.h>
#include "Mesh.h"
#include "Transform.h"

using namespace std;

const int MAX_NUMBER_OF_LIGHTS = 256;

class PointLight
{
private:
	Mesh mesh;
	Transform transform;
	glm::vec3 color;
public:
	PointLight();
	Mesh& GetMesh();

	glm::vec3& GetPos();
	glm::vec3& GetScale();
	glm::vec3& GetColor();
	
	Transform *getTransform();
	void Draw();
	virtual ~PointLight();
};

class PointLightHandler
{
private:
	PointLight lightArray[MAX_NUMBER_OF_LIGHTS];
	GLuint nrOfLights;

	GLuint loc_position[MAX_NUMBER_OF_LIGHTS];
	GLuint loc_color[MAX_NUMBER_OF_LIGHTS];
	GLuint loc_NrOfLights;
public:
	PointLightHandler();

	// location, pos, color
	void createLight(glm::vec3 position, glm::vec3 color);

	void sendToShader();
	void initiateLights(GLuint *program);
	void Draw(int index);

	GLuint getNrOfLights();
	Transform *getTransform(int index);

	virtual ~PointLightHandler();
};

#endif