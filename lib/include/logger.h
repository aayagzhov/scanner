/**
 * @file logger.h
 * @brief Logging facility for scan operations
 * @author scanner
 * @date 2025
 * 
 * @details
 * This file defines a simple logging class that writes scan results and messages
 * to a file or standard output.
 */

#pragma once

#include "core.h"

#include <string>
#include <fstream>

namespace scanner {
/**
 * @class Logger
 * @brief Provides logging functionality for scan operations
 * 
 * @details
 * The Logger class writes formatted log messages to a specified output file.
 * It supports three-part messages for consistent formatting.
 */
class Logger final {
public:
    using Str = std::string;  ///< String type alias

    /**
     * @brief Default constructor
     */
    explicit Logger() { }

    /**
     * @brief Sets the output file for logging
     * @param file_path Path to the log file
     */
    void set_output_file(const std::string &file_path);

    /**
     * @brief Writes a formatted log message
     * @param lhs Left part of the message (typically timestamp or category)
     * @param med Middle part (typically the main message)
     * @param rhs Right part (typically additional information or status)
     */
    void log(const Str &lhs, const Str &med, const Str &rhs);

    /**
     * @brief Boolean conversion operator to check if logger is active
     * @return true if logger is active and ready, false otherwise
     */
    explicit operator bool() const noexcept {
        return active;
    }

private:
    bool active{false};        ///< Indicates if logger is active
    std::fstream file;         ///< Output file stream
};

} // namespace scanner
