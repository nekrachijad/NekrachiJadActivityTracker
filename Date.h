//
// Created by jadne on 12/06/2025.
//

#ifndef DATE_H
#define DATE_H


class Date {
protected:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year);
    Date():day(0),month(0),year(0){}

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    void setDay(int day);

    void setMonth(int month);

    void setYear(int year);

    bool isLeapYear(int year) const;

    bool validDay(int day, int month, int year) const;

    bool validMonth(int month);

    bool validYear(int year);

    bool validDate(int day, int month, int year);

    int getDaysOfMonth(int month, int year) const;

    bool operator==(const Date &date) const;

};


#endif //DATE_H
