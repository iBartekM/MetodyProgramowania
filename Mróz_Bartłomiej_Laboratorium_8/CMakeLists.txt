cmake_minimum_required(VERSION 3.20)
project(Mroz_Bartlomiej_Laboratorium_8)

set(CMAKE_CXX_STANDARD 17)

# Program 1: Problem plecakowy (ogolny) — programowanie dynamiczne
add_executable(Program_01 "Mróz_Bartłomiej_Program_01.cpp" LibKnapsackDP.cpp)

# Program 2: Problem plecakowy — rekurencja (suma podzbioru)
add_executable(Program_02 "Mróz_Bartłomiej_Program_02.cpp" LibSubsetSum.cpp)
