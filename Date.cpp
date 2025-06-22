//
// Created by jadne on 12/06/2025.
//

#include "Date.h"
#include <stdexcept>

Date::Date(int day, int month, int year) {
    if (!validDate(day, month, year))
        throw std::out_of_range("DATA NON VALIDA!");
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

void Date::setDay(int day) {
    if (validDay(day, this->month, this->year))
        Date::day = day;
    else
        throw std::out_of_range("GIORNO NON VALIDO!");
}

void Date::setMonth(int month) {
    if (validMonth(month)) {
        if (validDay(this->day, month,this->year))
            Date::month = month;
        else
            throw std::out_of_range("GIORNO NON VALIDO!");
    } else
        throw std::out_of_range("MESE NON VALIDO!");
}

void Date::setYear(int year) {
    if (validYear(year)) {
        if (validDay(this->day, month,this->year))
            Date::year = year;
        else
            throw std::out_of_range("GIORNO NON VALIDO!");
    } else
        throw std::out_of_range("ANNO NON VALIDO!");
}

bool Date::validDay(int day, int month, int year) const {
    int maxDays = getDaysOfMonth(month, year);
    if (day > 0 && day <= maxDays)
        return true;
    return false;
}

bool Date::validMonth(int month) {
    if (month > 0 && month < 13)
        return true;
    return false;
}

bool Date::validYear(int year) {
    if (year >= 2000 && year <= 2100)
        return true;
    return false;
}

bool Date::validDate(int day, int month, int year) {
    if (validDay(day, month, year) && validMonth(month) && validYear(year))
        return true;
    else
        return false;
}

bool Date::isLeapYear(int year) const {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return true;
            else
                return false;
        } else
            return true;
    }
    return false;
}


int Date::getDaysOfMonth(int month, int year) const {
    switch (month) {
        case 2:
            // febbraio bisestile
            if (isLeapYear(year))
                return 29;
            else
                return 28;
            break;
        case 4:
        // aprile
        case 6:
        // giugno
        case 9:
        // settembre
        case 11:
            // novembre
            return 30;
        default:
            // tutti gli altri mesi
            return 31;
    }
}

bool Date::operator==(const Date &date) const {
    if (this->day == date.day && this->month == date.month && this->year == date.year)
        return true;
    return false;
}



