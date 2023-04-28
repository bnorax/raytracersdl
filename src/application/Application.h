#pragma once
#include <renderer/VulkanRenderer.h>
#include <scene/Scene.h>
#include <scene/systems/Systems.h>

class Application {
public:
	Application();
	int OnExecute();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnInitializeVulkan();
	~Application();

	SDL_Window* getWindow();
	std::tuple<int, int> getWindowDimensions();
private:
	bool running;
	int32_t windowWidth = 1280, windowHeight = 720;
	SDL_Window* sdlWindow = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;


	std::unique_ptr<Scene> activeScene;
	std::unique_ptr<Systems> systems;
	std::unique_ptr<VulkanRenderer> renderer;
};