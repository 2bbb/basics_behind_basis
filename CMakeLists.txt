cmake_minimum_required(VERSION 3.3)
project(basics_behind_basis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

include_directories(include)
add_executable(basics_behind_basis ${SOURCE_FILES})