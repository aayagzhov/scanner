/**
 * @file scanner.h
 * @brief Main scanner class for file system scanning and malware detection
 * @author scanner
 * @date 2025
 * 
 * @details
 * This file defines the main Scanner class that coordinates file scanning,
 * hash calculation, and malware detection using a hash database.
 */

#pragma once

#include "base.h"
#include "export.h"
#include "core.h"
#include "hasher.h"
#include "logger.h"

#include <mutex>
#include <string>

namespace scanner {

/**
 * @class Scanner
 * @brief Main scanner class that orchestrates file scanning and analysis
 * 
 * @details
 * The Scanner class provides functionality to scan directories, calculate file hashes,
 * check them against a malware database, and log results. It uses multiple components
 * including Base for database operations, Hasher for hash calculation, and Logger for output.
 */
class Scanner final {
public:
   /**
    * @brief Default constructor
    */
   Scanner() {};

   /**
    * @brief Sets the malware database file
    * @param base_file Path to the malware database file
    */
   void set_base(const std::string &base_file);

   /**
    * @brief Sets the log output file
    * @param log_file Path to the log file
    */
   void set_log(const std::string &log_file);

   /**
    * @brief Sets statistics collection object
    * @param st Reference to Stat object for collecting scan statistics
    */
   void set_stat(Stat &st);

   /**
    * @brief Scans a directory recursively for malware
    * @param folder_path Path to the directory to scan
    * 
    * @details
    * This method scans all files in the specified directory and its subdirectories,
    * calculates MD5 hashes, checks them against the malware database, and logs results.
    */
   void scan(const std::string &folder_path);

private:
   /**
    * @brief Processes a single file: calculates hash and checks against database
    * @param file Path to the file to process
    */
   void process_file(const std::string &file);

   Base base;           ///< Malware database handler
   Logger logger;       ///< Logging facility
   Hasher hasher;       ///< Hash calculator
   Stat *stat{nullptr}; ///< Statistics collector

   std::mutex mtx;      ///< Mutex for thread-safe operations
};

} // namespace scanner
