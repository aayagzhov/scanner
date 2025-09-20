#include "hasher.h"

#include <gtest/gtest.h>

using namespace std::string_literals;

namespace scanner {

TEST(General, add) {
    Hasher hasher;
    hasher.get_hash(PROJECT_ROOT + "/tests/data/random_text.txt"s);
    EXPECT_EQ(8, 3 + 5);
}

} // namespace scanner