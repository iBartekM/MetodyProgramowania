cmake_minimum_required(VERSION 4.0)
project(MP_LAB_3_MAIN)

set(CMAKE_CXX_STANDARD 20)

add_executable(MP_LAB_3_MAIN main.cpp LibSearch.cpp LibFiles.cpp)
add_executable(gen_test gen_test.cpp)
