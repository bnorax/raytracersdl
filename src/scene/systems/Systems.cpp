#include "Systems.h"

Systems::Systems()
{
	camera = std::make_unique<CameraSystem>();
}

void Systems::Start()
{

}

void Systems::Update()
{
	camera->Update();
}
