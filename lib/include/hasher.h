#pragma once

#include "core.h"
#include "md5.h"

#include <algorithm>
#include <array>
#include <string>
#include <fstream>

#include <iostream>
#include <cassert>

namespace scanner {

/// @brief Find MD-5 hash for input file
class Hasher final {
public:
    using Message = std::string;

    std::pair<Hash, Message> get_hash(const std::string &file_path) const {
        std::ifstream file(file_path, std::ios::in | std::ios::binary);

        if (!file) {
            return {"", "Can't open input file"};
        }
        MD5 md5;
        static const int BUFF_SIZE = 2048; // take 2 KB of RAM
        std::array<uint8_t, BUFF_SIZE> buffer;
        do {
            file.read(reinterpret_cast<char*>(buffer.data()), BUFF_SIZE);
            uint64_t len = file.gcount();
            md5.update(buffer.data(), file.gcount());
        } while(file);

        if(!file.eof()) {
            return {"", "File read error"};
        }
        return {md5.finish(), ""};
    }

private:
};

} // namespace scanner
