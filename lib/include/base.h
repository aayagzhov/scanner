#pragma once

#include "core.h"

#include <unordered_map>
#include <string>

namespace scanner {

class Base final {
public:
    explicit Base(const std::string &file) {
        /// TODO: read base from file;
    //         std::ifstream file("data.csv");
    // if (!file.is_open()) {
    //     std::cerr << "Не удалось открыть файл.\n";
    //     return 1;
    // }

    // std::string line;
    // while (std::getline(file, line)) {
    //     // Найти позицию символа ';'
    //     size_t pos = line.find(';');
    //     if (pos == std::string::npos) {
    //         std::cerr << "Строка не содержит ';': " << line << "\n";
    //         continue;
    //     }

    //     // Получить две подстроки
    //     std::string first = line.substr(0, pos);
    //     std::string second = line.substr(pos + 1);

    //     std::cout << "Первая: " << first << ", Вторая: " << second << "\n";
    // }

    // file.close();
    // return 0;
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
