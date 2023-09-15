cmake_minimum_required(VERSION 3.22)

project(Hakoirimusume)

add_compile_options(-Werror -Wall  -Wextra -g )

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(Hakoirimusume_lib nomalmethod.cpp)
target_link_libraries (Hakoirimusume_lib Eigen3::Eigen)

add_executable(Hakoirimusume main.cpp)
target_link_libraries(Hakoirimusume PRIVATE Hakoirimusume_lib)
add_executable(test_methods test_method.cpp)
target_link_libraries(test_methods PRIVATE GTest::gtest GTest::gtest_main Hakoirimusume_lib )


gtest_discover_tests(test_methods)
