include_directories(${gtest_SOURCE_DIR}/include)
link_directories(${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES bdd.cc unittest.cc)
add_executable(unitTest ${TEST_SOURCE_FILES})
target_link_libraries(unitTest gtest gtest_main fyramid)