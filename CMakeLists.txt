cmake_minimum_required(VERSION 3.25)

project(RayTracer
    VERSION 1.0
    DESCRIPTION "Ray Tracer SDL VULKAN"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

find_package(Vulkan REQUIRED shaderc_combined)
find_package(SDL2 REQUIRED)
add_compile_definitions(VULKAN_HPP_NO_CONSTRUCTORS)
add_compile_definitions(SDL_MAIN_HANDLED)

add_executable(RayTracer src/main.cpp src/main.h src/application.cpp src/application.h src/vulkancontext.cpp src/vulkancontext.h src/shaderutils.cpp src/shaderutils.h)
target_link_libraries(RayTracer PRIVATE SDL2::SDL2 Vulkan::Vulkan Vulkan::shaderc_combined)
target_precompile_headers(RayTracer PRIVATE ${Vulkan_INCLUDE_DIRS}/vulkan/vulkan_raii.hpp)

install(FILES $<TARGET_RUNTIME_DLLS:RayTracer> DESTINATION $<TARGET_FILE_DIR:RayTracer>)