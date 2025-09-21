#include "base.h"

#include <gtest/gtest.h>

using namespace std::string_literals;

namespace scanner {

TEST(Base, in_base) {
    Base base;
    base.load(PROJECT_ROOT + "/tests/data/base.csv"s);
    EXPECT_EQ(base.get_verdict("8ee70903f43b227eeb971262268af5a8"),
              "Downloader");
}


TEST(Base, not_in_base) {
    Base base;
    base.load(PROJECT_ROOT + "/tests/data/base.csv"s);
    EXPECT_EQ(base.get_verdict("8ee70903f43b2274eb971262268af548"), "");
}

} // namespace scanner