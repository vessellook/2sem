cmake_minimum_required(VERSION 3.15)
project(dynamic_array C)

set(CMAKE_C_STANDARD 99)

add_executable(dynamic_array main.c dynamic_array.c dynamic_array_int.c dynamic_array_complex.c)
add_executable(test_int test_int.c dynamic_array.c dynamic_array_int.c)
add_executable(test_complex test_complex.c dynamic_array.c dynamic_array_complex.c)