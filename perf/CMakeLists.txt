find_package(benchmark)

add_executable(perf perf.cpp)
target_link_libraries(perf benchmark::benchmark_main SolutionsSrc data_source)
