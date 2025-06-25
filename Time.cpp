//
// Created by jadne on 22/06/2025.
//

#include "Time.h"

Time::Time(int h, int m) {
    if (h < 0 || h > 23 || m < 0 || m > 59)
        throw std::invalid_argument("Ora non valida");

    hours = h;
    minutes = m;
}

int Time::calculateMinutes() const {
    return hours * 60 + minutes;
}

bool Time::operator<(const Time &other) const {
    return calculateMinutes() < other.calculateMinutes();
}

bool Time::operator>=(const Time &other) const {
    return calculateMinutes() >= other.calculateMinutes();
}

int Time::operator-(const Time &altra) const {
    return this->calculateMinutes() - altra.calculateMinutes();
}
