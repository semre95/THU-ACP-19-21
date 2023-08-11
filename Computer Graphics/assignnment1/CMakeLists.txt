cmake_minimum_required(VERSION 3.3)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

set(MySource src/assignment1/homework1.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(FreeType REQUIRED)
find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)

include_directories(include)
include_directories(include/SOIL)

aux_source_directory(src/SOIL SOILSource)
add_library(SOIL ${SOILSource})
add_library(glad src/glad/glad.c)

add_executable(Assignment1 ${MySource})

target_link_libraries(Assignment1 OpenGL::GL glfw glad SOIL ${FREETYPE_LIBRARIES} ${CORE_FOUNDATION_LIBRARY})
target_include_directories(Assignment1 PRIVATE ${FREETYPE_INCLUDE_DIRS})
