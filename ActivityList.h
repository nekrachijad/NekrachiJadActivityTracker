//
// Created by jadne on 22/06/2025.
//

#ifndef ACTIVITYLIST_H
#define ACTIVITYLIST_H

#include <vector>
#include "Activity.h"
#include "Date.h"

class ActivityList {
protected:
    std::vector<Activity> activities;

public:
    ActivityList() = default;

    virtual ~ActivityList() = default;

    void addActivity(const Activity &activity);

    std::vector<Activity> getActivitiesByDate(const Date &date) const;

    void printActivitiesByDate(const Date &date) const;

    std::vector<Activity> getAllActivities() const { return activities; }

    void removeActivity(const std::string& description);


    void modifyActivity(int index, const Activity &nuova) {
        if (index >= 0 && index < activities.size()) {
            activities[index] = nuova;
        }
    }

};

#endif // ACTIVITYLIST_H


