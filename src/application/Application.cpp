#include "Application.h"
#include <iostream>

Application::Application()
{
    mRunning = true;
    mWindow = nullptr;
    mRenderer = nullptr;
    if (SDL_Init(SDL_INIT_EVERYTHING)) throw std::runtime_error(std::string("Error during SDL initializtion\n").append(SDL_GetError()));
    mWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, SDL_WINDOW_VULKAN);
    if (mWindow == NULL) throw std::runtime_error(std::string("Error during SDL window creation\n").append(SDL_GetError()));
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if(mRenderer == NULL) throw std::runtime_error(std::string("Error during SDL renderer creation\n").append(SDL_GetError()));
    mVulkanContext = std::make_unique<VulkanContext>(mWindow);
}

int Application::OnExecute()
{
    SDL_Event event;
    while (mRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
    return 0;
}

void Application::OnEvent(SDL_Event* event)
{
    if (event->type == SDL_QUIT)
    {
        mRunning = false;
    }
}

void Application::OnLoop()
{
}

void Application::OnRender()
{
    mVulkanContext->Draw();
   // SDL_SetRenderDrawColor(mRenderer, 100, 20, 30, 255);
    //SDL_RenderClear(mRenderer);
    //SDL_RenderPresent(mRenderer);

}

Application::~Application()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    SDL_Quit();
}
