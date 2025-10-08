/**
 * @file base.h
 * @brief Malware hash database management
 * @author scanner
 * @date 2025
 * 
 * @details
 * This file defines the Base class for loading and querying a malware hash database.
 * The database maps MD5 hashes to verdict strings.
 */
#pragma once

#include "core.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>

namespace scanner {

/**
 * @class Base
 * @brief Malware hash database loader and query interface
 * 
 * @details
 * The Base class loads a malware database from a file and provides efficient
 * lookup of hashes to determine if files are malicious.
 */
class Base final {
public:
    /**
     * @brief Default constructor
     */
    explicit Base() { }

    /**
     * @brief Loads malware database from file
     * @param file_path Path to the database file
     * 
     * @details
     * The database file should contain lines with hash-verdict pairs,
     * typically in the format: "HASH VERDICT"
     */
    void load(const std::string &file_path);

    /**
     * @brief Checks if a hash exists in the database
     * @param hash MD5 hash to look up
     * @return true if hash is found in database, false otherwise
     */
    bool find_hash(const Hash &hash) const;

    /**
     * @brief Gets the verdict for a hash
     * @param hash MD5 hash to look up
     * @return Verdict string if found, empty string otherwise
     */
    Verdict get_verdict(const Hash &hash) const;

    /**
     * @brief Boolean conversion operator to check if database is loaded
     * @return true if database is loaded and active, false otherwise
     */
    explicit operator bool() const noexcept {
        return active;
    }

private:
    bool active{false};                     ///< Indicates if database is loaded
    std::unordered_map<Hash, Verdict> data; ///< Hash to verdict mapping
};

} // namespace scanner
