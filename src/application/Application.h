#pragma once
#include <renderer/VulkanContext.h>
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
	bool mRunning;
	int32_t mWindowWidth = 1280,mWindowHeight = 720;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	std::unique_ptr<VulkanContext> mVulkanContext;
};