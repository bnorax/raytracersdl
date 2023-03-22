cmake_minimum_required(VERSION 3.25)

project(RayTracer
    VERSION 1.0
    DESCRIPTION "Ray Tracer SDL"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

include(FetchContent)

fetchcontent_declare(SDL2 URL https://github.com/libsdl-org/SDL/releases/download/release-2.26.4/SDL2-devel-2.26.4-VC.zip)
fetchcontent_makeavailable(SDL2)

find_package(Vulkan)
add_compile_definitions(VULKAN_HPP_NO_CONSTRUCTORS)

find_package(SDL2)
add_executable(RayTracer src/main.cpp src/main.h src/application.cpp src/application.h src/vulkancontext.cpp src/vulkancontext.h)
target_link_libraries(RayTracer PRIVATE ${SDL2_LIBRARIES} Vulkan::Vulkan)
target_include_directories(RayTracer PRIVATE ${SDL2_INCLUDE_DIRS})
target_precompile_headers(RayTracer PRIVATE ${Vulkan_INCLUDE_DIRS}/vulkan/vulkan_raii.hpp)

install(FILES $<TARGET_RUNTIME_DLLS:RayTracer> DESTINATION $<TARGET_FILE_DIR:RayTracer>)