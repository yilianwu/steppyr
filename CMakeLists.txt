cmake_minimum_required(VERSION 3.12)
project(steppyr VERSION 1.0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Python3 3.7 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)
find_package(pigpio REQUIRED)

add_subdirectory(steppyr_cpp)
