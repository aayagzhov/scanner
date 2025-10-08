/**
 * @file hasher.h
 * @brief File hashing interface
 * @author scanner
 * @date 2025
 * 
 * @details
 * This file defines the interface for calculating file hashes with additional
 * metadata such as file size and status messages.
 */

#pragma once

#include "core.h"

#include <string>
#include <tuple>

namespace scanner {
/**
 * @class Hasher
 * @brief Calculates MD5 hashes for files
 * 
 * @details
 * The Hasher class provides functionality to calculate MD5 hashes for files
 * and return additional information about the operation.
 */
/// @brief Find MD-5 hash for input file
class Hasher final {
public:
    /**
     * @brief Calculates MD5 hash for a file
     * @param file_path Path to the file to hash
     * @return Tuple containing:
     *         - Hash: The calculated MD5 hash (empty string on error)
     *         - Message: Status message (error description or success)
     *         - uint64_t: File size in bytes (0 on error)
     */
    std::tuple<Hash, Message, uint64_t> find_hash(const std::string &file_path);
};

} // namespace scanner
