#pragma once
#include <SDL.h>
#include "VulkanContext.h"

class Application {
public:
	Application();

	int OnExecute();
	bool OnInitialize();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnExit();

	void OnInitializeVulkan();
private:
	bool mRunning;
	int32_t mWindowWidth = 1280,mWindowHeight = 720;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	std::unique_ptr<VulkanContext> mVulkanContext;
};