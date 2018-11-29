#include "PointLight.h"

PointLightHandler::PointLightHandler()
{
	this->nrOfLights = 0;
}

void PointLightHandler::createLight(glm::vec3 position, glm::vec3 color)
{
	this->lightArray[this->nrOfLights].GetMesh().createMesh("ObjectFiles/moon.obj", color);
	this->lightArray[this->nrOfLights].GetPos() = position;
	this->lightArray[this->nrOfLights].GetColor() = color;
	this->lightArray[this->nrOfLights].GetScale() = glm::vec3(0.2f,0.2f,0.2f);

	this->nrOfLights++;
}

void PointLightHandler::sendToShader()
{
	// Send the lights
	for (int i = 0; i < this->nrOfLights; i++)
	{
		glm::vec3 position = this->lightArray[i].GetPos();
		glm::vec3 color = this->lightArray[i].GetColor();
		glUniform3f(loc_position[i], position.x, position.y, position.z);
		glUniform3f(loc_color[i], color.x, color.y, color.z);
	}

	// Send the nrOfLights variable
	glUniform1i(this->loc_NrOfLights, this->nrOfLights);
}

void PointLightHandler::initiateLights(GLuint *program)
{
	char name[128];
	
	// Tell the gpu the names of the uniforms
	for (int i = 0; i < this->nrOfLights; i++)
	{
		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "PointLights[%d].position", i);
		loc_position[i] = glGetUniformLocation(*program, name);

		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "PointLights[%d].color", i);
		loc_color[i] = glGetUniformLocation(*program, name);
	}

	this->loc_NrOfLights = glGetUniformLocation(*program, "NR_OF_POINT_LIGHTS");
}

void PointLightHandler::Draw(int index)
{
	lightArray[index].Draw();
}

GLuint PointLightHandler::getNrOfLights()
{
	return this->nrOfLights;
}

Transform *PointLightHandler::getTransform(int index)
{
	return this->lightArray[index].getTransform();
}

PointLightHandler::~PointLightHandler()
{

}

PointLight::PointLight()
{

}

Mesh & PointLight::GetMesh()
{
	return this->mesh;
}

glm::vec3 & PointLight::GetPos()
{
	return this->transform.GetPos();
}

glm::vec3 & PointLight::GetScale()
{
	return this->transform.GetScale();
}

glm::vec3 & PointLight::GetColor()
{
	return this->color;
}

Transform *PointLight::getTransform()
{
	return &this->transform;
}

void PointLight::Draw()
{
	this->mesh.Draw();
}

PointLight::~PointLight()
{

}
