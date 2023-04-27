#include "Systems.h"

Systems::Systems(entt::registry& _registry)  : registry{_registry}
{
	camera = std::make_unique<CameraSystem>(registry);
}

void Systems::Start()
{

}

void Systems::Update()
{
	camera->Update();
}
