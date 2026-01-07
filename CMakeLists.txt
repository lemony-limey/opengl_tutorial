cmake_minimum_required(VERSION 4.1)
project(opengl_tutorial VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)

add_executable(opengl_tutorial
        src/main.cpp
        src/config.hpp
)

target_include_directories(opengl_tutorial PRIVATE dependencies)

find_package(glfw3 REQUIRED)
target_link_libraries(opengl_tutorial glfw)
