//
// Created by jadne on 22/06/2025.
//

#ifndef ACTIVITY_H
#define ACTIVITY_H


#include "Date.h"
#include <iostream>
#include "Time.h"

class Activity {
protected:
    static int nextId;
    int id;
    std::string description;
    Time start;
    Time end;
    Date data;

public:
    Activity(std::string description, Time inizio, Time fine, Date data);

    Activity(): description(""), start(0, 0), end(0, 0), data(1, 1, 2000) {
    }


    virtual ~Activity() = default;

    std::string getDescription() const {
        return description;
    }

    void setDescription(const std::string &description) {
        this->description = description;
    }

    Time getStart() const {
        return start;
    }

    void setStart(const Time &inizio) {
        this->start = inizio;
    }

    Time getEnd() const {
        return end;
    }

    void setEnd(const Time &fine);

    Date getData() const {
        return data;
    }

    void setData(const Date &data) {
        this->data = data;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }
};


#endif //ACTIVITY_H
