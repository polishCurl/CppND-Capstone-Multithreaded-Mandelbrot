cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17 -Wall -O2)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Mandelbrot src/main.cpp src/mandelbrot_viewer.cpp src/mandelbrot.cpp src/point.cpp src/barrier.cpp src/renderer.cpp src/controller.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Mandelbrot ${SDL2_LIBRARIES} pthread)
