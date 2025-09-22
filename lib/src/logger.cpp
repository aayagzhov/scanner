#include "logger.h"

#include <iostream>

namespace scanner {

bool Logger::set_output_file(const std::string &file_path) {
    if (active) {
        return false;
    }
    file.open(file_path, std::ios::out | std::ios::trunc);
    active = file.is_open();
    return active;
}

void Logger::log(const Str &lhs, const Str &med, const Str &rhs) {
    file << lhs << ";" << med << ";" << rhs << "\n";
}

} // namespace scanner
