#include <gtest/gtest.h>
extern "C" {
    #include "../src/include/add.h"
    #include "../src/include//subtract.h"
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(AddTest, BasicTests) {
    EXPECT_EQ(add(2, 3), 5) << "These are equal!";
    EXPECT_EQ(subtract(5, 3), 2) << "These are equal!";
}