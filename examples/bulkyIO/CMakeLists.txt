set(BULKYIO_SOURCE_FILES bulkyIO.cpp)
add_executable(bulkyIO ${BULKYIO_SOURCE_FILES})
target_link_libraries(bulkyIO fyramid)
