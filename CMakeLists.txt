cmake_minimum_required(VERSION 3.25)

project(RayTracer
    VERSION 1.0
    DESCRIPTION "Ray Tracer SDL"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

include(FetchContent)

fetchcontent_declare(SDL2 
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.4
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
fetchcontent_makeavailable(SDL2)

fetchcontent_declare(glm 
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
fetchcontent_makeavailable(glm)

find_package(Vulkan REQUIRED)

add_compile_definitions(VULKAN_HPP_NO_CONSTRUCTORS)
add_compile_definitions(SDL_MAIN_HANDLED)

add_executable(RayTracer src/main.cpp src/main.h src/application.cpp src/application.h src/vulkancontext.cpp src/vulkancontext.h)
target_link_libraries(RayTracer PRIVATE SDL2 glm Vulkan::Vulkan)
target_precompile_headers(RayTracer PRIVATE ${Vulkan_INCLUDE_DIRS}/vulkan/vulkan_raii.hpp)

install(FILES $<TARGET_RUNTIME_DLLS:RayTracer> DESTINATION $<TARGET_FILE_DIR:RayTracer>)