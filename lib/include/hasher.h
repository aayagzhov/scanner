#pragma once

#include "core.h"

#include <string>

namespace scanner {

/// @brief Find MD-5 hash for input file
class Hasher final {
public:
    std::pair<Hash, Message> find_hash(const std::string &file_path);

    uint64_t get_hashed_memory() {
        return hashed_memory;
    }

private:
    uint64_t hashed_memory{0ull};
};

} // namespace scanner
