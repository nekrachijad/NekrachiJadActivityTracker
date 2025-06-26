//
// Created by jadne on 22/06/2025.
//


#ifndef ORA_H
#define ORA_H

#include <iostream>
#include <stdexcept>

class Time {
protected:
    int hours;
    int minutes;

public:
    Time(int h = 0, int m = 0);

    int getHours() const {
        return hours;
    }

    void setHours(int ore) {
        this->hours = ore;
    }

    int getMinutes() const {
        return minutes;
    }

    void setMinutes(int minuti) {
        this->minutes = minuti;
    }

    int calculateMinutes() const;

    bool operator<(const Time &other) const;

    bool operator>=(const Time &other) const;

    int operator-(const Time& other) const;
};

#endif //ORA_H
