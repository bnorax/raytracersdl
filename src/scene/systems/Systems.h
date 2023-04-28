#pragma once
#include <scene/systems/CameraSystem.h>
#include <scene/Scene.h>
class Systems {
public:
	Systems(Scene& scene);
	void Start();
	void Update();
private:
	Scene& scene;
	std::unique_ptr<CameraSystem> camera;
};