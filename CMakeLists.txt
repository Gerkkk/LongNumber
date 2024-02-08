cmake_minimum_required(VERSION 3.27)
project(arithmlib)

add_subdirectory(Google_tests)

set(CMAKE_CXX_STANDARD 20)


add_library(Library STATIC Source/library.cpp)

add_executable(GetPi getpi/GetPi.cpp)
target_link_libraries(GetPi Library)

