//
// Created by jadne on 23/06/2025.
//

#include "gtest/gtest.h"
#include "../Ora.h"

TEST(OraTest, ConstructorTest) {
    Ora o(10, 30);
    EXPECT_EQ(o.getOre(), 10);
    EXPECT_EQ(o.getMinuti(), 30);

    Ora defaultOra;
    EXPECT_EQ(defaultOra.getOre(), 0);
    EXPECT_EQ(defaultOra.getMinuti(), 0);
}

TEST(OraTest, SetterGetterTest) {
    Ora o;
    o.setOre(15);
    o.setMinuti(45);
    EXPECT_EQ(o.getOre(), 15);
    EXPECT_EQ(o.getMinuti(), 45);
}

TEST(OraTest, CalcolaMinutiTest) {
    Ora o(2, 30);
    EXPECT_EQ(o.calcolaMinuti(), 150);

    o.setOre(0);
    o.setMinuti(45);
    EXPECT_EQ(o.calcolaMinuti(), 45);
}

TEST(OraTest, OperatorLessThanTest) {
    Ora o1(10, 15);
    Ora o2(11, 0);
    EXPECT_TRUE(o1 < o2);
    EXPECT_FALSE(o2 < o1);
    EXPECT_FALSE(o1 < o1);
}

TEST(OraTest, OperatorGreaterEqualTest) {
    Ora o1(10, 15);
    Ora o2(9, 45);
    Ora o3(10, 15);
    EXPECT_TRUE(o1 >= o2);
    EXPECT_TRUE(o1 >= o3);
    EXPECT_FALSE(o2 >= o1);
}

TEST(OraTest, OperatorDifferenceTest) {
    Ora o1(10, 30);
    Ora o2(9, 15);
    EXPECT_EQ(o1 - o2, 75);
    EXPECT_EQ(o2 - o1, -75);
    Ora o3(10, 30);
    EXPECT_EQ(o1 - o3, 0);
}