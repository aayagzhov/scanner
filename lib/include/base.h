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

    void load(const std::string &file_path) {
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

    bool find_hash(const Hash &hash) const {
        return data.count(hash);
    }

    Verdict get_verdict(const Hash &hash) const {
        if (data.count(hash)) {
            return data.at(hash);
        }
        return "";
    }

private:
    std::unordered_map<Hash, Verdict> data;
};

} // namespace scanner
