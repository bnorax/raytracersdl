#pragma once
#include <renderer/VulkanContext.h>
#include <renderer/Renderer.h>

#include <SDL2/SDL.h>

class Application {
public:
	Application();
	int OnExecute();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnInitializeVulkan();
	~Application();
private:
	bool running;
	int32_t windowWidth = 1280, windowHeight = 720;
	SDL_Window* sdlWindow = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;

	std::unique_ptr<Renderer> renderer;
};