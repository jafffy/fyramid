cmake_minimum_required(VERSION 3.6)
project(fyramid_prototype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(include src)

set(SOURCE_FILES src/fyramid.cc)
add_library(fyramid ${SOURCE_FILES})

enable_testing()

set(gtest_SOURCE_DIR deps/googletest/googletest)

add_subdirectory(${gtest_SOURCE_DIR})

include_directories(${gtest_SOURCE_DIR}/include)
link_directories(${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES tests/bdd.cc tests/unittest.cc)
add_executable(unitTest ${TEST_SOURCE_FILES})
target_link_libraries(unitTest gtest gtest_main fyramid)
