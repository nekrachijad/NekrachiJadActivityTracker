//
// Created by jadne on 23/06/2025.
//

#include "gtest/gtest.h"
#include "../Activity.h"

class ActivityTest : public ::testing::Test {
protected:
    Date data{22, 6, 2025};
    Ora inizio{9, 0};
    Ora fine{11, 30};
};

TEST_F(ActivityTest, ConstructorTest) {
    Activity act("Lezione", inizio, fine, data);

    EXPECT_EQ(act.getDescription(), "Lezione");
    EXPECT_EQ(act.getInizio().calcolaMinuti(), 540);  // 9 * 60
    EXPECT_EQ(act.getFine().calcolaMinuti(), 690);    // 11 * 60 + 30
    EXPECT_EQ(act.getData(), data);
}


TEST_F(ActivityTest, SetFineInvalidThrows) {
    Activity act("Test", inizio, fine, data);
    Ora fineNonValido{8, 0};

    EXPECT_THROW(act.setFine(fineNonValido), std::invalid_argument);
}
