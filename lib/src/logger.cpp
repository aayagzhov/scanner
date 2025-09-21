#include "logger.h"

#include <iostream>

namespace scanner {

bool Logger::set_output_file(const std::string &file_path) {
    if (file.is_open()) {
        return false;
    }
    file.open(file_path, std::ios::out | std::ios::app);
    return file.is_open();
}

bool Logger::log(const std::string file_path, const Hash &hash,
             const Verdict &verdict) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!file.is_open()) {
        return false;
    }

    file << file_path << " | " << hash << " | " << verdict << "\n";
    file.flush();
    return true;
}

} // namespace scanner
