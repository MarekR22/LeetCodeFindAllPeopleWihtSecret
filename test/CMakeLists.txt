find_package(Catch2)

add_executable(funTest SolutionTest.cpp)

target_link_libraries(funTest Catch2::Catch2WithMain SolutionsSrc data_source)

include(CTest)
include(Catch)
catch_discover_tests(funTest)
