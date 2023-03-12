#pragma once
#include <SDL.h>


class Application {
public:
	Application();

	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnExit();
private:
	bool isRunning;
	int windowWidth = 1280, windowHeight = 720;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
};