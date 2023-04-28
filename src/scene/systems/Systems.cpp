#include "Systems.h"

Systems::Systems(Scene& _scene)  : scene{_scene}
{
	camera = std::make_unique<CameraSystem>(scene);
}

void Systems::Start()
{

}

void Systems::Update()
{
	camera->Update();
}
