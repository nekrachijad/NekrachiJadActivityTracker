//
// Created by jadne on 22/06/2025.
//

#include "gtest/gtest.h"
#include "../Date.h"

TEST(DateTest, ConstructorTest) {
    Date date(15, 9, 2000);
    EXPECT_EQ(date.getDay(), 15);
    EXPECT_EQ(date.getMonth(), 9);
    EXPECT_EQ(date.getYear(), 2000);
}

