#include "CameraSystem.h"
#include <scene/components/Components.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>

CameraSystem::CameraSystem(Scene& _scene) : scene{ _scene },
											registry {_scene.getRegistry()}
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void CameraSystem::Update()
{
	using namespace Components;
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);

	auto regView = registry.view<Camera>();
	for (auto entity : regView) {
		Camera& camera = registry.get<Components::Camera>(entity);

		float xoffset = x;
		float yoffset = y;
		xoffset *= camera.sensitivityX;
		yoffset *= camera.sensitivityY;

		yaw = std::fmod((yaw - xoffset), 360.0f);
		//yaw -=  xoffset;
		pitch += yoffset;

		if (pitch > camera.maximumY) pitch = camera.maximumY;
		if (pitch < camera.minimumY) pitch = camera.minimumY;
		//std::cout << "Pitch: " << pitch << std::endl;
		//std::cout << "yaw: " << yaw << std::endl;

		UniformBufferObject& ubo = scene.getRenderer().getUBO();
		pos = glm::vec3(-3.0f, 0.0f, -15.0f);
		dir = glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
		up = glm::vec3(0.0f, -1.0f, 0.0f);
		ubo.view = glm::lookAtRH(pos, pos+glm::normalize(dir), up);
	}
}
