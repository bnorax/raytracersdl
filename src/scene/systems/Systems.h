#pragma once
#include <scene/systems/CameraSystem.h>

class Systems {
public:
	Systems();
	void Start();
	void Update();
private:
	std::unique_ptr<CameraSystem> camera;
};