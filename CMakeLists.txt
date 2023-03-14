cmake_minimum_required(VERSION 3.25)

project(RayTracer
    VERSION 1.0
    DESCRIPTION "Ray Tracer SDL"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

fetchcontent_declare(SDL2 URL https://github.com/libsdl-org/SDL/releases/download/release-2.26.4/SDL2-devel-2.26.4-VC.zip)
fetchcontent_makeavailable(SDL2)
include_directories("${CMAKE_CURRENT_LIST_DIR}/build/_deps/sdl2-src/include")

find_package(Vulkan)

add_executable(RayTracer src/main.cpp)
target_link_libraries(RayTracer PRIVATE SDL2::SDL2 SDL2::SDL2main Vulkan::Vulkan)


install(FILES SDL2::SDL2 DESTINATION $<TARGET_FILE_DIR:RayTracer>)