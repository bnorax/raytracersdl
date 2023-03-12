cmake_minimum_required(VERSION 3.25)

project(RayTracer
    VERSION 1.0
    DESCRIPTION "Ray Tracer SDL"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

fetchcontent_declare(SDL2 URL https://github.com/libsdl-org/SDL/releases/download/release-2.26.4/SDL2-devel-2.26.4-VC.zip)
fetchcontent_makeavailable(SDL2)
set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/build/_deps/sdl2-src/include")
set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/build/_deps/sdl2-src/lib/x64")

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(RayTracer src/main.cpp)
target_link_libraries(RayTracer ${SDL2_LIBRARIES}/SDL2.lib ${SDL2_LIBRARIES}/SDL2main.lib)

install(FILES ${SDL2_LIBRARIES}/SDL2.dll DESTINATION $<TARGET_FILE_DIR:RayTracer>)