cmake_minimum_required(VERSION 3.21)
project(graphs)

add_compile_options(-Wall -Wshadow -fPIC)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphs main.cpp ArcGraph.cpp ListGraph.cpp MatrixGraph.cpp)
