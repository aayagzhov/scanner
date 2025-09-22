#include "logger.h"

#include <filesystem>
#include <iostream>

namespace scanner {

void Logger::set_output_file(const std::string &file_path) {
    if (active) {
        throw std::runtime_error("log file is already provide");
    }

    std::filesystem::path path(file_path);

    if (!path.has_parent_path() || !std::filesystem::exists(path.parent_path())) {
        throw std::runtime_error("directory for log file does not exist: ["
                + path.parent_path().string() + "]");
    }

    file.open(file_path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("failed to create log file: ["
                + file_path + "]");
    }

    active = true;
}

void Logger::log(const Str &lhs, const Str &med, const Str &rhs) {
    file << lhs << ";" << med << ";" << rhs << "\n";
}

} // namespace scanner
