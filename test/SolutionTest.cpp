#include <catch2/catch_all.hpp>

#include <Solution.hpp>
#include <data.hpp>

auto& lazyLargeTestData()
{
    static test_data::Data result = test_data::loadDataFrom("large.json");
    return result;
}

TEST_CASE("check large test data")
{
    const auto& meetings = lazyLargeTestData().meetings;
    
    int i = 1;
    for (const auto& meeting : meetings) {
        CAPTURE(i);
        CHECK(meeting[2] == 1);
        REQUIRE(meeting[0] == i + 1);
        REQUIRE(meeting[1] == i);
        ++i;
    }
    REQUIRE(i == 10001);
}

TEMPLATE_TEST_CASE("findAllPeople", "[solutions]", my2::Solution, leetcode::Solution, my::Solution)
{
    using Catch::Matchers::UnorderedEquals;
    
    auto d = GENERATE(values<test_data::Data>({
        {
            6,
            { { 1, 2, 5 }, { 2, 3, 8 }, { 1, 5, 10 } },
            1,
            { 0, 1, 2, 3, 5 },
        },
        {
            4,
            { { 3, 1, 3 }, { 1, 2, 2 }, { 0, 3, 3 } },
            3,
            { 0, 1, 3 },
        },
        {
            5,
            { { 3, 4, 2 }, { 1, 2, 1 }, { 2, 3, 1 } },
            1,
            { 0, 1, 2, 3, 4 },
        },
        {
            5,
            { { 4, 3, 1 }, { 3, 2, 1 }, { 2, 1, 1 } },
            4,
            { 0, 1, 2, 3, 4 }
        },
        {
            5,
            { { 4, 3, 2 }, { 3, 2, 2 }, { 2, 1, 1 } },
            4,
            { 0, 2, 3, 4 }
        },
        {
            5,
            { { 4, 3, 3 }, { 3, 2, 2 }, { 2, 1, 1 } },
            4,
            { 0, 3, 4 }
        },
        lazyLargeTestData(),
    }));
    
    CAPTURE(d.n, d.meetings, d.first_person);

    TestType solution;
    REQUIRE_THAT(solution.findAllPeople(d.n, d.meetings, d.first_person), UnorderedEquals(d.expected));
}
