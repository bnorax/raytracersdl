#include "Renderer.h"

Renderer::Renderer(SDL_Window* _window) : window {_window}
{
	vulkanContext = std::make_unique<VulkanContext>(window);
}

void Renderer::Draw()
{
	vulkanContext->Draw();
}
