#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambientV_,
	float diffuseV_, float specularV_, glm::vec3 LightColour_)
{
	position = position_;
	ambientV = ambientV_;
	diffuseV = diffuseV_;
	specularV = specularV_;
	LightColour = LightColour_;

}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::Getposition() const
{
	return position;
}

float LightSource::GetambientV() const
{
	return ambientV;
}

float LightSource::GetdiffuseV() const
{
	return diffuseV;
}

float LightSource::GetspecularV() const
{
	return specularV;
}

glm::vec3 LightSource::GetLightColour() const
{
	return LightColour;
}

void LightSource::Setposition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetambientV(float ambientV_)
{
	ambientV = ambientV_;
}

void LightSource::SetdiffuseV(float diffuseV_)
{
	diffuseV = diffuseV_;
}

void LightSource::SetspecularV(float specularV_)
{
	specularV = specularV_;
}
