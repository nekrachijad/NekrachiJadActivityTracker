//
// Created by jadne on 12/06/2025.
//

#include "Date.h"

Date::Date(int d, int m, int y){
    day = d;
    month = m;
    year = y;
}

int Date::getDay() const {
    return day;
}

void Date::setDay(int day) {
    this->day = day;
}

int Date::getMonth() const {
    return month;
}

void Date::setMonth(int month) {
    this->month = month;
}

int Date::getYear() const {
    return year;
}

void Date::setYear(int year) {
    this->year = year;
}