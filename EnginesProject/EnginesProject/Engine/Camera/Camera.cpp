#include "Camera.h"

#include "../Core/CoreEngine.h"

Camera::Camera(): position(glm::vec3()), fieldOfView(0.0f), forward(glm::vec3()), up(glm::vec3()),
right(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f),
yaw(0.0f), pitch(0.0f), perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 1.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	//if this was set to 0 then it will be pointed to the right
	yaw = -90.0f;
	//direction of camera looking up and down
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView,
		CoreEngine::GetInstance()->GetScreenWidth() /
		CoreEngine::GetInstance()->GetScreenHeight(),
		nearPlane, farPlane);
	//left and right plane
	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(),
		0.0f, CoreEngine::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	if (lightsources.size() > 0) {
		//This will create temp local var
		//auto means will auto set key type
//auto is not needed but do it anyways
		for (auto m : lightsources) {
			delete m;
			m = nullptr;
		}
		lightsources.clear();
	}
	
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

void Camera::AddLightSources(LightSource* lightsources_)
{
	lightsources.push_back(lightsources_);
}

glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

std::vector<LightSource*> Camera::GetLightsources() const
{
	return lightsources;
}



void Camera::UpdateCameraVectors()
{
	//update for all
	//humans like to think in degrees but computers like to use radians *VERY IMPORTENT*
	//always convert to radians *VERY IMPORTENT*
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right =  glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));
	//this will always keep looking at targets direction
	view = glm::lookAt(position, position + forward, up);
}
