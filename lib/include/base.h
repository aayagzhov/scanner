#pragma once

#include "core.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>

namespace scanner {

class Base final {
public:
    explicit Base() { }

    void load(const std::string &file_path);

    bool find_hash(const Hash &hash) const;

    Verdict get_verdict(const Hash &hash) const;

private:
    std::unordered_map<Hash, Verdict> data;
};

} // namespace scanner
