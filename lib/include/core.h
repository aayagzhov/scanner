#pragma once

#include "export.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

namespace scanner {

using Hash    = std::string;
using Verdict = std::string;
using Message = std::string;

struct Stat {
    Stat();
    ~Stat();

    size_t elapsed_ms() const;

    std::string folder_path;
    std::string base_file;
    std::string log_file;

    size_t total_files_scanned = 0;
    size_t malicious_files_found = 0;
    size_t files_failed_to_analyze = 0;

    std::chrono::steady_clock::time_point start_time{};
    std::chrono::steady_clock::time_point end_time{};
};

std::string format_elapsed_ms(size_t ms_total);

std::ostream& operator<<(std::ostream& os, const Stat& stat);

} // namespace scanner