#pragma once

#include "core.h"

#include <string>
#include <mutex>
#include <fstream>

namespace scanner {

class Logger final {
public:
    explicit Logger() { }

    bool set_output_file(const std::string &file_path);

    bool log(const std::string file_path, const Hash &hash,
             const Verdict &cerdict);

private:
    std::mutex mtx;
    std::fstream file;
};

} // namespace scanner
