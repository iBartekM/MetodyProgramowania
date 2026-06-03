cmake_minimum_required(VERSION 3.20)
project(MP_LAB_5)

set(CMAKE_CXX_STANDARD 17)

# Program 1: graf skierowany - macierz incydencji
add_executable(prog1 prog1.cpp LibGraphMatrix.cpp)

# Program 2: graf nieskierowany - lista incydencji
add_executable(prog2 prog2.cpp LibGraphList.cpp)
