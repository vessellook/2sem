cmake_minimum_required(VERSION 3.15)
project(sequence)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)

add_executable(test_dynamic_array test_dynamic_array.cpp)
add_executable(test_linked_list test_linked_list.cpp)

add_executable(test_sequence test_sequence.cpp)

add_executable(test_matrix test_matrix.cpp)