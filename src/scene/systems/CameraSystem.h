#pragma once
class CameraSystem {
public:
	CameraSystem(entt::registry&);
	void Update();
private:
	entt::registry& registry;
};