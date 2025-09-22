#include "md5.h"

#include <gtest/gtest.h>

#include <vector>

using namespace std::string_literals;

namespace scanner {

TEST(MD5, empty_text) {
    MD5 md5;
    EXPECT_EQ(md5.finish(), "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(MD5, single_char) {
    MD5 md5;
    md5.update(reinterpret_cast<const uint8_t*>("a"), 1);
    EXPECT_EQ(md5.finish(), "0cc175b9c0f1b6a831c399e269772661");
}

TEST(MD5, full_block) {
    MD5 md5;
    std::string block(64, 'x');
    md5.update(reinterpret_cast<const uint8_t*>(block.data()), block.size());
    EXPECT_EQ(md5.finish(), "c1bb4f81d892b2d57947682aeb252456");
}

TEST(MD5, all_bytes) {
    MD5 md5;
    std::vector<uint8_t> bytes(256);
    for (int i = 0; i < 256; ++i) bytes[i] = i;
    md5.update(bytes.data(), bytes.size());
    EXPECT_EQ(md5.finish(), "e2c865db4162bed963bfaa9ef6ac18f0");
}

TEST(MD5, same_parts) {
    MD5 md5;
    for (uint32_t i{0}; i < 3; ++i) {
        std::string str{";orighrwiuogjiorwjg"};
        md5.update(reinterpret_cast<const uint8_t*>(str.data()), str.size());
    }
    EXPECT_EQ(md5.finish(), "5e12b224f7ec78ba55c39aecb22628fe");
}

TEST(MD5, different_parts) {
    MD5 md5;
    std::vector<std::string> strs {
        "roghrwiogfjioarwjt4w09t94wqkfp94q42fjewipof",
        "q42",
        "09ri21ti429jgh9ro=-423ti05eogtgijnfkvobrnfj r",
        "kd",
        "bgoktjitekmtbot0tijino",
        "egtkmlgdb;l,",
        "fplforgjtigndjfkmrlp4lwrg"
    };
    for (uint32_t i{0}; i < strs.size(); ++i) {
        md5.update(reinterpret_cast<const uint8_t*>(strs[i].data()), strs[i].size());
    }
    EXPECT_EQ(md5.finish(), "fea92d6ed2541c0bcb40c89dc385c352");
}

} // namespace scanner