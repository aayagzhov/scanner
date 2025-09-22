#include "hasher.h"

#include <gtest/gtest.h>

using namespace std::string_literals;

namespace scanner {

TEST(Hasher, txt_32768_bytes) {
    Hasher hasher;
    auto hash = hasher.find_hash(PROJECT_ROOT + "/tests/data/data_32768.txt"s).first;
    EXPECT_EQ(hash, "2f491205caf3e5eb0c76d11a04bef635");
}

TEST(Hasher, txt_4159_bytes) {
    Hasher hasher;
    auto hash = hasher.find_hash(PROJECT_ROOT + "/tests/data/data_4159.txt"s).first;
    EXPECT_EQ(hash, "95611f4c4fba8c559fe86bdef1414918");
}

TEST(Hasher, webp) {
    Hasher hasher;
    auto hash = hasher.find_hash(PROJECT_ROOT + "/tests/data/data.webp"s).first;
    EXPECT_EQ(hash, "1bafa2b7b33e8e416336725080a3ee3e");
}

TEST(Hasher, png) {
    Hasher hasher;
    auto hash = hasher.find_hash(PROJECT_ROOT + "/tests/data/data.png"s).first;
    EXPECT_EQ(hash, "43a9e094e8ce3cb38c87ce82fb1a10be");
}

} // namespace scanner