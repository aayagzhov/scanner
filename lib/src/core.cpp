#include "core.h"

#include <string>
#include <iomanip>

namespace scanner {

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

} // namespace scanner