#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/glm.hpp>
#include <glew.h>
//dynamic size array
#include <vector>
using namespace std;
using namespace glm;
class LightSource
{
public:
	LightSource(glm::vec3 position_ = glm::vec3(), float ambientV_ = 0.0f,
		float diffuseV_ = 0.0f, float specularV_ = 0.0f,
		glm::vec3 LightColour_ = glm::vec3());
	~LightSource();
	
	vec3 Getposition() const;
	float GetambientV() const;
	float GetdiffuseV() const;
	float GetspecularV() const;
	vec3 GetLightColour() const;

	void Setposition(glm::vec3 position_);
	void SetambientV(float ambientV_);
	void SetdiffuseV(float diffuseV_);;
	void SetspecularV(float specularV_);
private:
	vec3 position;
	
	float ambientV;
	float diffuseV;
	float specularV;
	vec3 LightColour;
};
#endif