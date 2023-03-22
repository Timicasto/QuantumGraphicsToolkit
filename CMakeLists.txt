cmake_minimum_required(VERSION 3.24)
project(QuantumGraphicsToolkit)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(QuantumGraphicsToolkit main.cpp glad.c includes/qgt/utils.h)

include_directories(includes)
target_link_libraries(QuantumGraphicsToolkit Freetype::Freetype GL glfw)