/**
 * @file core.h
 * @brief Core types, structures, and utilities for the scanner
 * @author scanner
 * @date 2025
 * 
 * @details
 * This file contains common type definitions, the statistics structure,
 * and utility functions used throughout the scanner project.
 */
#pragma once

#include "export.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

namespace scanner {

using Hash    = std::string;  ///< Type for MD5 hash representation
using Verdict = std::string;  ///< Type for malware verdict
using Message = std::string;  ///< Type for general messages

/**
 * @struct Stat
 * @brief Statistics collection for scan operations
 * 
 * @details
 * This structure tracks various metrics during file scanning including
 * file counts, timing information, and memory usage.
 */
struct Stat {
    /**
     * @brief Default constructor - initializes start time
     */
    Stat() { start_time = std::chrono::steady_clock::now(); }

    /**
     * @brief Finalizes statistics by setting end time
     */
    void drop();

    /**
     * @brief Calculates elapsed time in milliseconds
     * @return Elapsed time in milliseconds
     */
    size_t elapsed_ms() const;

    std::string folder_path;              ///< Path to scanned folder
    std::string base_file;                ///< Path to malware database file
    std::string log_file;                 ///< Path to log file

    size_t total_files_scanned{0};        ///< Total number of files processed
    size_t malicious_files_found{0};      ///< Number of detected malicious files
    size_t files_failed_to_analyze{0};    ///< Number of files that couldn't be analyzed
    uint64_t hashed_memory{0ull};         ///< Total memory hashed in bytes

    std::chrono::steady_clock::time_point start_time{};  ///< Scan start time
    std::chrono::steady_clock::time_point end_time{};    ///< Scan end time
};

/**
 * @brief Formats milliseconds into human-readable time string
 * @param ms_total Time in milliseconds
 * @return Formatted time string (e.g., "1m 23s 456ms")
 */
std::string format_elapsed_ms(size_t ms_total);

/**
 * @brief Output operator for Stat structure
 * @param os Output stream
 * @param stat Statistics to output
 * @return Reference to the output stream
 */
std::ostream& operator<<(std::ostream& os, const Stat& stat);

} // namespace scanner