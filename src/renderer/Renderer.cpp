#include "Renderer.h"

Renderer::Renderer(SDL_Window* _window) : window {_window}
{
	vulkanContext = std::make_unique<VulkanContext>(window, time);
}

void Renderer::Draw()
{
	time.StartFrame();
	vulkanContext->Draw();
	time.EndFrame();
}
