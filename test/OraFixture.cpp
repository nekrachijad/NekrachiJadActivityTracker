//
// Created by jadne on 23/06/2025.
//

#include "gtest/gtest.h"
#include "../Time.h"

TEST(OraTest, ConstructorTest) {
    Time o(10, 30);
    EXPECT_EQ(o.getHours(), 10);
    EXPECT_EQ(o.getMinutes(), 30);

    Time defaultOra;
    EXPECT_EQ(defaultOra.getHours(), 0);
    EXPECT_EQ(defaultOra.getMinutes(), 0);
}

TEST(OraTest, SetterGetterTest) {
    Time o;
    o.setHours(15);
    o.setMinutes(45);
    EXPECT_EQ(o.getHours(), 15);
    EXPECT_EQ(o.getMinutes(), 45);
}

TEST(OraTest, CalcolaMinutiTest) {
    Time o(2, 30);
    EXPECT_EQ(o.calculateMinutes(), 150);

    o.setHours(0);
    o.setMinutes(45);
    EXPECT_EQ(o.calculateMinutes(), 45);
}

TEST(OraTest, OperatorLessThanTest) {
    Time o1(10, 15);
    Time o2(11, 0);
    EXPECT_TRUE(o1 < o2);
    EXPECT_FALSE(o2 < o1);
    EXPECT_FALSE(o1 < o1);
}

TEST(OraTest, OperatorGreaterEqualTest) {
    Time o1(10, 15);
    Time o2(9, 45);
    Time o3(10, 15);
    EXPECT_TRUE(o1 >= o2);
    EXPECT_TRUE(o1 >= o3);
    EXPECT_FALSE(o2 >= o1);
}

TEST(OraTest, OperatorDifferenceTest) {
    Time o1(10, 30);
    Time o2(9, 15);
    EXPECT_EQ(o1 - o2, 75);
    EXPECT_EQ(o2 - o1, -75);
    Time o3(10, 30);
    EXPECT_EQ(o1 - o3, 0);
}