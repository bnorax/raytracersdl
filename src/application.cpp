#include "Application.h"
#include <SDL_vulkan.h>

Application::Application()
{
    isRunning = true;
}

int Application::OnExecute()
{
    SDL_Event event;
    if (OnInit() == false)
    {
        return -1;
    }
    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
}

bool Application::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    pWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);
    if (pWindow != NULL)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    }
    else
    {
        return false;
    }
    return true;
}

void Application::OnEvent(SDL_Event* event)
{
    if (event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void Application::OnLoop()
{
}

void Application::OnRender()
{
    SDL_SetRenderDrawColor(pRenderer, 100, 20, 30, 255);
    SDL_RenderClear(pRenderer);
    SDL_RenderPresent(pRenderer);
}

void Application::OnExit()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    SDL_Quit();
}
