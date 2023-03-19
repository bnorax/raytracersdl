#include "Application.h"
#include <SDL_vulkan.h>

Application::Application()
{
    mRunning = true;
    mWindow = nullptr;
    mRenderer = nullptr;
}

int Application::OnExecute()
{
    SDL_Event event;
    if (OnInitialize() == false)
    {
        return -1;
    }
    while (mRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
}

bool Application::OnInitialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        return false;
    }

    mWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, 0);
    if (mWindow != NULL)
    {
        mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    } else {
        return false;
    }
    return true;
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
    SDL_SetRenderDrawColor(mRenderer, 100, 20, 30, 255);
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
}

void Application::OnExit()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    SDL_Quit();
}

void Application::OnInitializeVulkan()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
}