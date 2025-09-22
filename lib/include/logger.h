#pragma once

#include "core.h"

#include <string>
#include <fstream>

namespace scanner {

class Logger final {
public:
    using Str = std::string;

    explicit Logger() { }

    void set_output_file(const std::string &file_path);

    void log(const Str &lhs, const Str &med, const Str &rhs);

    explicit operator bool() const noexcept {
        return active;
    }

private:
    bool active{false};
    std::fstream file;
};

} // namespace scanner
