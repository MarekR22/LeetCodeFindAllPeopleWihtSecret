#pragma once

#include <filesystem>
#include <vector>

namespace test_data {
struct Data {
    int n;
    std::vector<std::vector<int>> meetings;
    int first_person;
    std::vector<int> expected;
};

Data loadDataFrom(std::filesystem::path p);
}
