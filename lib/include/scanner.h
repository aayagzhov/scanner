#pragma once

#include "base.h"
#include "export.h"
#include "core.h"
#include "hasher.h"
#include "logger.h"

#include <mutex>
#include <string>

namespace scanner {

class Scanner final {
public:
   Scanner() {};

   void set_base(const std::string &base_fale);

   void set_log(const std::string &log_file);

   void set_stat(Stat &st);

   void scan(const std::string &folder_path);

private:
   void process_file(const std::string &file);

   Base base;
   Logger logger;
   Hasher hasher;
   Stat *stat{nullptr};

   std::mutex mtx;
};

} // namespace scanner
