#pragma once
#include <SDL2/SDL.h>
#include <application/Time.h>

class Renderer {
public:
	Renderer(SDL_Window*);
	virtual void DrawFrame();
protected:
	SDL_Window* window;
	Time time;
};