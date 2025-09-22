#include "core.h"
#include "base.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>

namespace scanner {

void Base::load(const std::string &file_path) {
    active = true;
    std::ifstream file(file_path, std::ios::in);
    if (!file) {
        std::cerr << file_path << std::endl;
        assert(false && "open");
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(';');
        if (pos == std::string::npos) {
            std::cerr << "Строка не содержит ';': " << line << "\n";
            assert(false && "format");
        }

        Hash hash = line.substr(0, pos);
        Verdict verdict = line.substr(pos + 1);

        if (data.count(hash)) {
            assert(false && "already");
        }
        data[hash] = verdict;
    }

    file.close();
}

bool Base::find_hash(const Hash &hash) const {
    return data.count(hash);
}

Verdict Base::get_verdict(const Hash &hash) const {
    return data.at(hash);
}

} // namespace scanner
