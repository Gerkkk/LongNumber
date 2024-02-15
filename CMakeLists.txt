cmake_minimum_required(VERSION 3.8)
project(arithmlib)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(Library STATIC Source/library.cpp)
#add_subdirectory(Google_tests)

add_executable(GetPi get/GetPi.cpp)
target_link_libraries(GetPi Library)

enable_testing()
add_executable(Test testdir/Test.cpp)
target_link_libraries(Test Library)

target_link_libraries(Test GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(Test)