#pragma once

#include "base.h"
#include "export.h"
#include "core.h"

#include <string>
#include <iostream>
#include <iomanip>

namespace scanner {

struct Stat {
    size_t processed{0};
    size_t found{0};
    size_t mistakes{0};
    double time{0.};
};

std::ostream& operator<<(std::ostream& os, const Stat& stat) {
    const int label_width = 15;
    const int value_width = 10;

    os << std::left << std::setw(label_width) << "Параметр    | " 
       << std::left << std::setw(value_width) << "Значение" << "\n";
    os << std::string(label_width + value_width, '-') << "\n";

    // Добавляем пробелы после текста для выравнивания
    os << std::left << std::setw(label_width) << "Обработано  | " 
       << std::left << std::setw(value_width) << stat.processed << "\n";

    os << std::left << std::setw(label_width) << "Найдено     | " 
       << std::left << std::setw(value_width) << stat.found << "\n";

    os << std::left << std::setw(label_width) << "Ошибки      | " 
       << std::left << std::setw(value_width) << stat.mistakes << "\n";

    os << std::left << std::setw(label_width) << "Время (сек) | " 
       << std::left << std::setw(value_width) << std::fixed
       << std::setprecision(3) << stat.time << "\n";

    return os;
}

class Scanner final {
public:
    Scanner() {};

    void set_base(const std::string &base_fale) {

    }

    void set_log(const std::string &log_file) {

    }

    void scan(const std::string &folder_path) const {
        Stat stat;

   //  fs::path dir_path = "/path/to/directory";
   //  std::vector<std::future<void>> futures;

   //  try {
   //      for (const auto& entry : fs::recursive_directory_iterator(dir_path)) {
   //          if (fs::is_regular_file(entry.status())) {
   //              // Асинхронная обработка файла
   //              futures.push_back(std::async(std::launch::async, process_file, entry.path()));
   //          }
   //      }

   //      // Дождаться завершения всех потоков
   //      for (auto& f : futures) {
   //          f.get();
   //      }

   //  } catch (const fs::filesystem_error& e) {
   //      std::cerr << "Ошибка файловой системы: " << e.what() << std::endl;
   //  }

        std::cout << stat << std::endl;
    }

private:

};

} // namespace scanner
