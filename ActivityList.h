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


    std::vector<Activity> getAllActivities() const { return activities; }

    void removeActivityById(int id);
    void modifyActivityById(int id, const Activity& nuova);


};

#endif // ACTIVITYLIST_H


