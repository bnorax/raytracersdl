cmake_minimum_required(VERSION 3.26)
project(RayTracer
    VERSION 1.0
    DESCRIPTION "Ray Tracer SDL"
    LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_executable(RayTracer src/main.cpp)