cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

add_library(Library STATIC library.cpp)
add_executable(Test Test.cpp)
target_link_libraries(Test Library )
