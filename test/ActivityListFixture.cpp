//
// Created by jadne on 23/06/2025.
//

#include "gtest/gtest.h"
#include "../ActivityList.h"

TEST(ActivityList, AddActivityTest) {
    ActivityList lista;
    Date oggi{23, 6, 2025};
    lista.addActivity(Activity("Lezione", Time(9, 0), Time(10, 0), oggi));
    lista.addActivity(Activity("Studio", Time(14, 0), Time(16, 0), oggi));

    EXPECT_EQ(lista.getAllActivities().size(), 2);
}

TEST(ActivityList, GetActivitiesByDate) {
    ActivityList lista;
    Date oggi{23, 6, 2025};
    lista.addActivity(Activity("Lezione", Time(9, 0), Time(10, 0), oggi));
    lista.addActivity(Activity("Studio", Time(14, 0), Time(16, 0), oggi));

    auto result = lista.getActivitiesByDate(oggi);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getDescription(), "Lezione");
    EXPECT_EQ(result[1].getDescription(), "Studio");
}

TEST(ActivityList, RemoveActivityTest) {
    ActivityList lista;
    Date oggi{23, 6, 2025};
    Date domani{24, 6, 2025};
    lista.addActivity(Activity("Lezione", Time(9, 0), Time(10, 0), oggi));
    lista.addActivity(Activity("Studio", Time(14, 0), Time(16, 0), oggi));
    lista.addActivity(Activity("Sport", Time(18, 0), Time(19, 0), domani));

    // Recupero l'id dell'attività "Studio" per rimuoverla
    int idToRemove = -1;
    for (const auto& act : lista.getAllActivities()) {
        if (act.getDescription() == "Studio") {
            idToRemove = act.getId();
            break;
        }
    }
    ASSERT_NE(idToRemove, -1); // controllo che id sia stato trovato

    lista.removeActivityById(idToRemove);
    EXPECT_EQ(lista.getAllActivities().size(), 2);
    EXPECT_EQ(lista.getAllActivities()[1].getDescription(), "Sport");
}

TEST(ActivityList, ModifyActivityTest) {
    ActivityList lista;
    Date oggi{23, 6, 2025};
    lista.addActivity(Activity("Lezione", Time(9, 0), Time(10, 0), oggi));
    lista.addActivity(Activity("Studio", Time(14, 0), Time(16, 0), oggi));

    // Recupero l'id dell'attività in posizione 0 per modificarla
    int idToModify = lista.getAllActivities()[0].getId();

    Activity nuova("Esame", Time(12, 0), Time(13, 0), oggi);
    lista.modifyActivityById(idToModify, nuova);

    EXPECT_EQ(lista.getAllActivities()[0].getDescription(), "Esame");
}

