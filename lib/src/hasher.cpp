#include "hasher.h"
#include "md5.h"

#include <algorithm>
#include <array>
#include <string>
#include <fstream>

namespace scanner {

std::tuple<Hash, Message, uint64_t> Hasher::find_hash(const std::string &file_path) {
    std::ifstream file(file_path, std::ios::in | std::ios::binary);

    if (!file) {
        return {"", "Error: cannot open file", 0ull};
    }
    MD5 md5;
    static const int BUFF_SIZE = 2048; // take 2 KB of RAM
    std::array<uint8_t, BUFF_SIZE> buffer;
    uint64_t hashed_memory{0ull};
    do {
        file.read(reinterpret_cast<char*>(buffer.data()), BUFF_SIZE);
        uint64_t len = file.gcount();
        hashed_memory += len;
        md5.update(buffer.data(), len);
    } while(file);

    if(!file.eof()) {
        return {"", "Error: read failure in file", hashed_memory};
    }
    return {md5.finish(), "", hashed_memory};
}

} // namespace scanner
