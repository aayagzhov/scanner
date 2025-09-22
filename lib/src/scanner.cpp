#include "scanner.h"
#include "export.h"
#include "thread_pool.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace scanner {

void Scanner::set_base(const std::string &base_fale) {
   base.load(base_fale);
}

void Scanner::set_log(const std::string &log_file) {
   logger.set_output_file(log_file);
}

void Scanner::set_stat(Stat &st) {
   this->stat = &st;
}

void Scanner::scan(const std::string &folder_path) {
   if (!base) {
      throw std::runtime_error("scan error: hash database is not loaded");
   }
   if (!logger) {
      throw std::runtime_error("scan error: log file is not provide");
   }

   ThreadPool thread_pool;

   for (const auto& entry : fs::recursive_directory_iterator(folder_path)) {
      if (entry.is_regular_file()) {
         std::string file_path = entry.path().string();
         thread_pool.add_task([this, file_path] {
               this->process_file(file_path);
         });
      }
   }

   stat->hashed_memory = hasher.get_hashed_memory();
}

void Scanner::process_file(const std::string &file) {
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
      logger.log(hash, verdict, file);
   } else {
      std::lock_guard<std::mutex> lock(mtx);
      size_t count{0};
      verdict = in_base ? base_verdict : "Hash not in base";
      count += (size_t)in_base;
      if (stat) {
         ++stat->total_files_scanned;
         stat->malicious_files_found += count;
      }
      logger.log(hash, verdict, file);
   }
}

} // namespace scanner
