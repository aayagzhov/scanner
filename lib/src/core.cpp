#include "core.h"

namespace scanner {

Stat::Stat() : start_time(std::chrono::steady_clock::now()) { }

Stat::~Stat() {
   end_time = std::chrono::steady_clock::now();
   std::cout << *this << std::endl;
}

size_t Stat::elapsed_ms() const {
   using namespace std::chrono;
   if (end_time < start_time) return 0;
   return duration_cast<milliseconds>(end_time - start_time).count();
}

std::string format_elapsed_ms(size_t ms_total) {
    using namespace std::chrono;
    if (ms_total < 0) ms_total = 0;

    long long ms = ms_total % 1000;
    long long total_seconds = ms_total / 1000;
    long long seconds = total_seconds % 60;
    long long total_minutes = total_seconds / 60;
    long long minutes = total_minutes % 60;
    long long hours = total_minutes / 60;

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << hours << ':'
        << std::setw(2) << minutes << ':'
        << std::setw(2) << seconds << '.'
        << std::setw(3) << ms;
    return oss.str();
}

inline std::ostream& operator<<(std::ostream& os, const Stat& stat) {
    os << "Scan report\n"
       << "-----------\n"
       << "Root path:        " << stat.folder_path << '\n'
       << "Database file:    " << stat.base_file << '\n'
       << "Log file:         " << stat.log_file << "\n\n";

    os << "Total files scanned:           " << stat.total_files_scanned << '\n'
       << "Malicious files found:         " << stat.malicious_files_found << '\n'
       << "Files failed to analyze:       " << stat.files_failed_to_analyze << '\n'
       << "Elapsed time:                  " << format_elapsed_ms(stat.elapsed_ms()) << '\n'
       << "Total data hashed:             " << (stat.hashed_memory >> 10) << " KB "<<'\n';

    return os;
}

} // namespace scanner