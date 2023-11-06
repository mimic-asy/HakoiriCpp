cmake_minimum_required(VERSION 3.22)

project(Hakoirimusume)

add_compile_options(-O3 -g)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include_directories(include)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(Hakoirimusume_lib graph.cpp puzzle.cpp shortest_clear_logic.cpp)
target_link_libraries (Hakoirimusume_lib Eigen3::Eigen)

add_executable(Hakoirimusume main.cpp)
target_link_libraries(Hakoirimusume PRIVATE Hakoirimusume_lib)
