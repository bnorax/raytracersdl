#include "CameraSystem.h"
#include <scene/components/Components.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>

CameraSystem::CameraSystem(entt::registry& _registry) : registry{ _registry }
{
}

void CameraSystem::Update()
{
	using namespace Components;
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	auto regView = registry.view<Camera>();
	for (auto entity : regView) {
		//Components::Transforms& transform = registry.get<Components::Transforms>(entity);
		Camera& camera = registry.get<Components::Camera>(entity);

		//float screenWidth = renderer.windowRef.width, screenHeight = renderer.windowRef.height;
		float screenWidth = 1280, screenHeight = 720;
		float distX = x - screenWidth / 2;
		float distY = y - screenHeight / 2;
		float anglePerPixelX = (camera.maximumY - camera.minimumY) / screenWidth, anglePerPixelY = (camera.maximumX - camera.minimumX) / screenHeight;
		float yaw = anglePerPixelX * distX;
		float yawRadian = yaw * glm::pi<float>()/180.0f;
		float pitch = anglePerPixelY * distY;
		float pitchRadian = pitch * glm::pi<float>() / 180.0f;

		glm::quat qPitch = glm::angleAxis(pitchRadian, glm::vec3(1, 0, 0));
		glm::quat qYaw = glm::angleAxis(yawRadian, glm::vec3(0, 1, 0));
		glm::quat orientation = qPitch * qYaw;
		orientation = glm::normalize(orientation);
	}


}
