cmake_minimum_required(VERSION 4.1)
project(opengl_tutorial VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)

# Define the executable
add_executable(opengl_tutorial
        src/main.cpp
        src/config.hpp
        src/glad.c
)

# The executable needs the stuff in the "dependencies" directory
target_include_directories(opengl_tutorial PRIVATE dependencies)

# Find GLFW and link it
find_package(glfw3 REQUIRED)
target_link_libraries(opengl_tutorial glfw)

# Find OpenGL and link it
find_package(OpenGL REQUIRED)
target_link_libraries(opengl_tutorial OpenGL::GL)
