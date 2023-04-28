#pragma once
#include <scene/Scene.h>
#include <graphics/Vertex.h>

class CameraSystem {
public:
	CameraSystem(Scene&);
	void Update();
private:
	Scene& scene;
	entt::registry& registry;

	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

	float yaw = 0, pitch = 0;
};