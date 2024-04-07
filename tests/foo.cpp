#include <gtest/gtest.h>
extern "C" {
    #include <core/card.h>
    #include "core/add.h"
}

TEST(FooTest, CardTest) {
    add_card(123456789, 1234, 1000);
    ASSERT_EQ(add(2, 3), 4);
}