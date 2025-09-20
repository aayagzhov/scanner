#include "md5.h"

#include <gtest/gtest.h>

using namespace std::string_literals;

namespace scanner {

TEST(MD5, general) {
    MD5 md5;
    std::string str{"1firofgnrasoingasorjfrjfoa"};
    md5.update(reinterpret_cast<const uint8_t*>(str.data()), str.size());
}

} // namespace scanner