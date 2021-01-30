cmake_minimum_required(VERSION 3.12)
project(steppyr VERSION 1.0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find python and Boost - both are required dependencies
find_package(Python3 3.7 COMPONENTS Development REQUIRED)
find_package(Boost 1.67 COMPONENTS python3 REQUIRED)

add_subdirectory(src)
