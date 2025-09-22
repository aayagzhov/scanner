#include "scanner.h"
#include "core.h"

#include <gtest/gtest.h>

using namespace std::string_literals;

namespace scanner {

TEST(Scanner, scan_rep) {
    Stat stat;
    Scanner scanner;
    scanner.set_base(PROJECT_ROOT + "/tests/data/base.csv"s);
    scanner.set_log(PROJECT_ROOT + "log.log"s);
    scanner.set_stat(stat);
    scanner.scan(PROJECT_ROOT);
    EXPECT_EQ(stat.malicious_files_found, 1);
}

} // namespace scanner