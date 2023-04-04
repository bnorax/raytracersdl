#pragma once
#include <renderer/VulkanContext.h>

class Renderer {
public:
	Renderer();
private:
	std::unique_ptr<VulkanContext> vulkanContext;

};