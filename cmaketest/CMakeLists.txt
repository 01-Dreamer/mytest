cmake_minimum_required(VERSION 3.22)
project(main)


file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main ${SRC})