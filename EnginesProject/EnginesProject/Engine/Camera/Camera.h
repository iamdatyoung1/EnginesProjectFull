#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>
class Camera
{
public:
	//constructor
	Camera();
	~Camera();
	//we need both for position and rotation of camera
	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);
	void AddLightSources(LightSource* lightsources_);
	
	glm::mat4 GetView() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	glm::mat4 GetPerspective() const;
	std::vector<LightSource*> GetLightsources() const;
private:
	
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> lightsources;
	//LightSource* lightsources;
};
#endif