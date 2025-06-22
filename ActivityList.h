//
// Created by jadne on 22/06/2025.
//

#ifndef ACTIVITYLIST_H
#define ACTIVITYLIST_H

#include <vector>
#include "Activity.h"
#include "Date.h"

class ActivityList {
private:
    std::vector<Activity> activities;

public:
    void addActivity(const Activity& activity);

    std::vector<Activity> getActivitiesByDate(const Date& date) const;

    void printActivitiesByDate(const Date& date) const;
};

#endif // ACTIVITYLIST_H


