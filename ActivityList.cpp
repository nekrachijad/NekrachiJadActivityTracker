//
// Created by jadne on 22/06/2025.
//

#include "ActivityList.h"

#include "ActivityList.h"
#include <iostream>

void ActivityList::addActivity(const Activity& activity) {
    activities.push_back(activity);
}

std::vector<Activity> ActivityList::getActivitiesByDate(const Date& date) const {
    std::vector<Activity> result;
    for (const auto& activity : activities) {
        if (activity.getData() == date) {
            result.push_back(activity);
        }
    }
    return result;
}

void ActivityList::printActivitiesByDate(const Date& date) const {
    auto result = getActivitiesByDate(date);
    if (result.empty()) {
        std::cout << "Nessuna attività trovata per il "
                  << date.getDay() << "/"
                  << date.getMonth() << "/"
                  << date.getYear() << ".\n";
        return;
    }

    std::cout << "Attività del "
              << date.getDay() << "/"
              << date.getMonth() << "/"
              << date.getYear() << ":\n";

    for (const auto& activity : result) {
        std::cout << "- " << activity.getDescription()
                  << " dalle " << activity.getInizio().getOre() << ":" << activity.getInizio().getMinuti()
                  << " alle " << activity.getFine().getOre() << ":" << activity.getFine().getMinuti()
                  << "\n";
    }
}
