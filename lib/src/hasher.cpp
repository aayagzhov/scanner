#include "hasher.h"
#include "md5.h"

#include <algorithm>
#include <array>
#include <string>
#include <fstream>

namespace scanner {

std::pair<Hash, Message> Hasher::find_hash(const std::string &file_path) const {
    std::ifstream file(file_path, std::ios::in | std::ios::binary);

    if (!file) {
        return {"", "Error: cannot open file"};
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
        return {"", "Error: read failure in file"};
    }
    return {md5.finish(), ""};
}

} // namespace scanner
