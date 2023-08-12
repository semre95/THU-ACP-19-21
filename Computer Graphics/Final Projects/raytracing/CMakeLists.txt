cmake_minimum_required (VERSION 2.8)
project (ray_tracing)

add_definitions(-std=c++11)
find_package(Threads REQUIRED)
include_directories(include)

add_executable(ray_tracing src/main.cpp src/bmp.cpp src/camera.cpp src/color.cpp src/light.cpp src/primitive.cpp src/raytracer.cpp src/scene.cpp src/vector3.cpp)
target_link_libraries(ray_tracing Threads::Threads)