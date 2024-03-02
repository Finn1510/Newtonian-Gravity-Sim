cmake_minimum_required(VERSION 3.7)

project(newtSim)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(newtSim main.cpp)
target_link_libraries(newtSim ${SDL2_LIBRARIES})