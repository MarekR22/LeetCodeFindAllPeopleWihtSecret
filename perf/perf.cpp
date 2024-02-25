#include <benchmark/benchmark.h>
#include <Solution.hpp>
#include <data.hpp>

const auto TestData = test_data::loadDataFrom("large.json");

template <typename ImplTag>
void testIt(benchmark::State& state) {
    ImplTag impl;
    auto data = TestData;
    for (auto _ : state) {
        benchmark::DoNotOptimize(data);
        benchmark::DoNotOptimize(impl.findAllPeople(data.n, data.meetings, data.first_person));
    }
}

BENCHMARK_TEMPLATE(testIt, my::Solution);
BENCHMARK_TEMPLATE(testIt, leetcode::Solution);
BENCHMARK_TEMPLATE(testIt, my2::Solution);
