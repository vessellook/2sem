cmake_minimum_required(VERSION 3.12)
project(sequence)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(main main.cpp)

add_executable(test_dynamic_array tests/test_dynamic_array.cpp)
add_executable(test_linked_list tests/test_linked_list.cpp)

add_executable(test_sequence tests/test_sequence.cpp)

add_executable(test_matrix tests/test_matrix.cpp)

add_executable(input_system input_in_mess.cpp ui/fsm.cpp)

add_executable(modified_input_system .test2.cpp ui/fsm.cpp)

add_executable(quick_test .quick_test.cpp)