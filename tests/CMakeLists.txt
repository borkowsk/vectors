cmake_minimum_required(VERSION 3.27)
project(test_vectors)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_vectors main.cpp
                            vectors.h
)
