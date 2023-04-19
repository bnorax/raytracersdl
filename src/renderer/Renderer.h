#pragma once
#include <application/Time.h>

class Renderer {
public:
	Renderer(SDL_Window*);
	virtual void DrawFrame();
	virtual void Start();
protected:
	SDL_Window* window;
	Time time;
};