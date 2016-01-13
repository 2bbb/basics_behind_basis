cmake_minimum_required(VERSION 3.3)
project(basics_behind_basis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(bit_by_bit/bit_by_bit)
include_directories(basics_behind_basis)

add_subdirectory(tests)
