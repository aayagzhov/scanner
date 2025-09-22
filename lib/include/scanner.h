#pragma once

#include "base.h"
#include "export.h"
#include "core.h"
#include "thread_pool.h"
#include "hasher.h"
#include "logger.h"
#include <chrono>

#include <filesystem>
#include <string>
#include <mutex>

namespace fs = std::filesystem;

namespace scanner {

class Scanner final {
public:
   Scanner() {};

   void set_base(const std::string &base_fale) {
      if (!base) {
         base.load(base_fale);
      }
   }

   void set_log(const std::string &log_file) {
      if (!logger) {
         logger.set_output_file(log_file);
      }
   }

   void set_stat(Stat &st) {
      this->stat = &st;
   }

   bool scan(const std::string &folder_path) {
      if (!base || !logger) {
         std::cerr << "Scan error: database or log file not initialized" << std::endl;
         return false;
      }
      ThreadPool thread_pool;
      try {
         for (const auto& entry : fs::recursive_directory_iterator(folder_path)) {
            if (entry.is_regular_file()) {
               std::string file_path = entry.path().string();
               thread_pool.add_task([this, file_path] {
                  this->process_file(file_path);
               });
            }
         }
      } catch (const fs::filesystem_error& e) {
         std::cerr << "Scan error (file system mistake): " << e.what() << std::endl;
         return false;
      }
      return true;
   }

private:
   void process_file(const std::string &file) {
      auto [hash, verdict] = hasher.find_hash(file);
      bool in_base{base.find_hash(hash)};
      Verdict base_verdict = in_base ? base.get_verdict(hash) : " ";

      if (hash.empty()) {
         std::lock_guard<std::mutex> lock(mtx);
         if (stat) {
            hash = "################################";
            ++stat->total_files_scanned;
            ++stat->files_failed_to_analyze;
         }
         logger.log(file, hash, verdict);
      } else {
         std::lock_guard<std::mutex> lock(mtx);
         size_t count{0};
         verdict = "Hash not in base";
         if (in_base) {
            verdict = base_verdict;
            ++count;
         }
         if (stat) {
            ++stat->total_files_scanned;
            stat->malicious_files_found += count;
         }
         logger.log(hash, verdict, file);
      }
   }

   Base base;
   Logger logger;
   Hasher hasher;
   Stat *stat{nullptr};

   std::mutex mtx;
};

} // namespace scanner
