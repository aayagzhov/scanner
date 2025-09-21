#pragma once

#include "core.h"

#include <string>

namespace scanner {

/// @brief Find MD-5 hash for input file
class Hasher final {
public:
    std::pair<Hash, Message> find_hash(const std::string &file_path) const;
};

} // namespace scanner
