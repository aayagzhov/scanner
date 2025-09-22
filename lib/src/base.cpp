#include "core.h"
#include "base.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>

namespace scanner {

void Base::load(const std::string &file_path) {
    if (active) {
        throw std::runtime_error("hash database is already loaded");
    }

    std::ifstream file(file_path, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open hash database file: ["
                                 + file_path + "]");
    }

    std::string line;
    size_t line_number = 0;

    while (std::getline(file, line)) {
        ++line_number;
        size_t pos = line.find(';');
        if (pos == std::string::npos) {
            throw std::runtime_error("invalid format of hash database at line " + std::to_string(line_number) +
                                     ": missing ';' in line \"" + line + "\"");
        }

        Hash hash = line.substr(0, pos);
        Verdict verdict = line.substr(pos + 1);

        if (data.count(hash)) {
            throw std::runtime_error("duplicate hash in hash database at line " + std::to_string(line_number) +
                                     ": " + hash);
        }
        data[hash] = verdict;
    }

    if (file.bad()) {
        throw std::runtime_error("i/o error while reading hash database file: [" + file_path + "]");
    }

    active = true;
}


bool Base::find_hash(const Hash &hash) const {
    return data.count(hash);
}

Verdict Base::get_verdict(const Hash &hash) const {
    return data.at(hash);
}

} // namespace scanner
