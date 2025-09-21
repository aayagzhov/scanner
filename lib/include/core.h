#pragma once

#include <string>

namespace scanner {

using Hash    = std::string;
using Verdict = std::string;
using Message = std::string;

struct Stat {
    size_t processed{0};
    size_t found{0};
    size_t mistakes{0};
    double time{0.};
};

std::ostream& operator<<(std::ostream& os, const Stat& stat);

} // namespace scanner