add_library(SolutionsSrc)
target_sources(SolutionsSrc
    PRIVATE
        Solution.cpp
    PUBLIC
        Solution.hpp)

target_include_directories(SolutionsSrc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
