#include "data.hpp"
#include "directories.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace test_data {
using json = nlohmann::json;

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Data, n, meetings, first_person, expected);

Data loadDataFrom(std::filesystem::path p)
{
    Data result{};
    std::ifstream f{std::filesystem::path{ResorceDir} / p};
    from_json(json::parse(f), result);
    
    return result;
}
}
