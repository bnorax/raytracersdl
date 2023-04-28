#include "Application.h"

Application::Application()
{
    running = true;

    if (SDL_Init(SDL_INIT_EVERYTHING)) throw std::runtime_error(std::string("Error during SDL initializtion\n").append(SDL_GetError()));
    sdlWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_VULKAN);
    if (sdlWindow == NULL) throw std::runtime_error(std::string("Error during SDL window creation\n").append(SDL_GetError()));
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
    if(sdlRenderer == NULL) throw std::runtime_error(std::string("Error during SDL renderer creation\n").append(SDL_GetError()));

    renderer = std::make_unique<VulkanRenderer>(sdlWindow);
    activeScene = std::make_unique<Scene>(*renderer);
    systems = std::make_unique<Systems>(*activeScene);

    systems->Start();
    activeScene->Start();
    renderer->Start();
}

int Application::OnExecute()
{
    SDL_Event event;
    while (running)
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
        running = false;
    }
}

void Application::OnLoop()
{
    activeScene->Update();
    systems->Update();
}

void Application::OnRender()
{
    renderer->DrawFrame();
   // SDL_SetRenderDrawColor(mRenderer, 100, 20, 30, 255);
    //SDL_RenderClear(mRenderer);
    //SDL_RenderPresent(mRenderer);

}

Application::~Application()
{
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}

SDL_Window* Application::getWindow()
{
    return sdlWindow;
}

std::tuple<int, int> Application::getWindowDimensions()
{
    return std::tuple<int, int>(windowWidth, windowHeight);
}
