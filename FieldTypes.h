#pragma once
#include <vector>
#include <map>
#include <string>
#include <array>

using scalarField = std::vector<std::vector<double>>;
using scalarFieldMap = std::map<std::string, scalarField*>;

using tensor = std::array<std::array<double, 2>, 2>;
