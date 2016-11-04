cmake_minimum_required(VERSION 3.6)
project(fyramid_prototype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Source files
include_directories(include src)

add_subdirectory(src)

# For testing
set(gtest_SOURCE_DIR deps/googletest/googletest)
add_subdirectory(${gtest_SOURCE_DIR})

add_subdirectory(tests)


