#pragma once

#include "core.h"

#include <string>
#include <tuple>

namespace scanner {

/// @brief Find MD-5 hash for input file
class Hasher final {
public:
    std::tuple<Hash, Message, uint64_t> find_hash(const std::string &file_path);
};

} // namespace scanner
