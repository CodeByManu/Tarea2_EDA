cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

set(CMAKE_MAKE_PROGRAM "MinGW Makefiles")
# set the project name

project(laberinto
VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_subdirectory(src)
#add_subdirectory(tests)

add_executable(test main.cpp maze/maze.cpp ADT's/linkedList.cpp ADT's/node.cpp ADT's/queue.cpp ADT's/stack.cpp)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/include)

# add the executable