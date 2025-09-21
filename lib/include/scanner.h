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

namespace fs = std::filesystem;

namespace scanner {

class Scanner final {
public:
   Scanner() {};

   void set_base(const std::string &base_fale) {
      base.load(base_fale);
   }

   void set_log(const std::string &log_file) {
      logger.set_output_file(log_file);
   }

   void scan(const std::string &folder_path) {
      auto start = std::chrono::steady_clock::now();
      {
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
         std::cerr << "Ошибка файловой системы: " << e.what() << std::endl;
      }
      }
      auto end = std::chrono::steady_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      stat.time = duration.count();
   }

   void print_stat() const {
      std::cout << stat << std::endl;
   }

private:
   void process_file(const std::string &file) {
      auto [hash, verdict] = hasher.find_hash(file);
      if (base.find_hash(hash)) {
         verdict = base.get_verdict(hash);
      }
      //stat + stat
      logger.log(file, hash, verdict);
   }

   Base base;
   Stat stat;
   Logger logger;
   Hasher hasher;
};

} // namespace scanner
