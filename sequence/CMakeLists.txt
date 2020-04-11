cmake_minimum_required(VERSION 3.12)
project(sequence)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(main main.cpp)

add_executable(test_dynamic_array tests/test_dynamic_array.cpp)
add_executable(test_linked_list tests/test_linked_list.cpp)

add_executable(test_sequence tests/test_sequence.cpp)

add_executable(test_matrix tests/test_matrix.cpp)

#add_executable(other .test.cpp)
