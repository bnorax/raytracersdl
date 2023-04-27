#pragma once
#include <scene/systems/CameraSystem.h>
#include <scene/Scene.h>
class Systems {
public:
	Systems(entt::registry&);
	void Start();
	void Update();
private:
	entt::registry& registry;
	std::unique_ptr<CameraSystem> camera;
};