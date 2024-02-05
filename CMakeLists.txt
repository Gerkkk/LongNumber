cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_library(Library STATIC Source/library.cpp)
add_executable(Test Source/Test.cpp)
target_link_libraries(Test Library)
