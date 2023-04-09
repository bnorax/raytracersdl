#pragma once
#include <renderer/VulkanContext.h>

#include <SDL2/SDL.h>
#include <application/Time.h>

class Renderer {
public:
	Renderer(SDL_Window*);
	void Draw();
private:
	SDL_Window* window;
	std::unique_ptr<VulkanContext> vulkanContext;
	Time time;
};