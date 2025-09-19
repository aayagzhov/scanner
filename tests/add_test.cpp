#include <add.h>

#include <gtest/gtest.h>

TEST(General, add) {
    EXPECT_EQ(8, add(3, 5));
}