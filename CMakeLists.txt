cmake_minimum_required(VERSION 3.16)

project(LeetCodeProblem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(data_source)
add_subdirectory(test)
add_subdirectory(perf)
