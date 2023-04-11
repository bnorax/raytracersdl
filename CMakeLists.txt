cmake_minimum_required(VERSION 3.25)

project(RayTracer
    VERSION 1.0
    DESCRIPTION "Ray Tracer SDL VULKAN"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
fetchcontent_declare(EnTT
                     GIT_REPOSITORY https://github.com/skypjack/entt.git
                     GIT_TAG        "v3.11.1")
fetchcontent_makeavailable(EnTT)
find_package(Vulkan REQUIRED shaderc_combined)
find_package(SDL2 REQUIRED)
add_compile_definitions(VULKAN_HPP_NO_CONSTRUCTORS)
add_compile_definitions(SDL_MAIN_HANDLED)


add_executable(RayTracer
                         src/application/main.cpp src/application/main.h 
                         src/application/application.cpp src/application/application.h 
                         src/application/time.cpp src/application/time.h
                         src/renderer/renderer.cpp src/renderer/renderer.h
                         src/renderer/vulkanrenderer.cpp src/renderer/vulkanrenderer.h
                         src/renderer/buffer.cpp src/renderer/buffer.h
                         src/graphics/vertex.h
                         src/shader/shader.cpp src/shader/shader.h)

set_target_properties(
    RayTracer PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:RayTracer>")

include_directories(src)
target_link_libraries(RayTracer PRIVATE Vulkan::Vulkan Vulkan::shaderc_combined SDL2::SDL2 EnTT::EnTT)
target_precompile_headers(RayTracer PRIVATE ${Vulkan_INCLUDE_DIRS}/vulkan/vulkan_raii.hpp)

install(FILES $<TARGET_RUNTIME_DLLS:RayTracer> DESTINATION $<TARGET_FILE_DIR:RayTracer>)
install(DIRECTORY "resources" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})