cmake_minimum_required(VERSION 3.21)
project(zero2prod_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
