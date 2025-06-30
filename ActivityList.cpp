//
// Created by jadne on 22/06/2025.
//

#include "ActivityList.h"
#include <iostream>

void ActivityList::addActivity(const Activity &activity) {
    activities.push_back(activity);
}

std::vector<Activity> ActivityList::getActivitiesByDate(const Date &date) const {
    std::vector<Activity> result;
    for (const auto &activity: activities) {
        if (activity.getData() == date) {
            result.push_back(activity);
        }
    }
    return result;
}

void ActivityList::removeActivityById(int id) {
    for (auto it = activities.begin(); it != activities.end();) {
        if (it->getId() == id) {
            it = activities.erase(it);
        } else {
            ++it;
        }
    }
}


void ActivityList::modifyActivityById(int id, const Activity &newActivity) {
    for (auto &activity: activities) {
        if (activity.getId() == id) {
            activity = newActivity;
            return;
        }
    }
}



