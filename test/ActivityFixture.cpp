//
// Created by jadne on 23/06/2025.
//

#include "gtest/gtest.h"
#include "../Activity.h"

TEST(Activity, ConstructorTest) {
    Date data{22, 6, 2025};
    Time inizio{9, 0};
    Time fine{11, 30};

    Activity act("Lezione", inizio, fine, data);

    EXPECT_EQ(act.getDescription(), "Lezione");
    EXPECT_EQ(act.getStart().calculateMinutes(), 540);  // 9 * 60
    EXPECT_EQ(act.getEnd().calculateMinutes(), 690);    // 11 * 60 + 30
    EXPECT_EQ(act.getData(), data);
}

TEST(Activity, SetFineInvalidThrows) {
    Date data{22, 6, 2025};
    Time inizio{9, 0};
    Time fine{11, 30};
    Activity act("Test", inizio, fine, data);

    Time fineNonValido{8, 0};

    EXPECT_THROW(act.setEnd(fineNonValido), std::invalid_argument);
}

