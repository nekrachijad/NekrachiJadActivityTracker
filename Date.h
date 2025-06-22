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

    Date():day(0), month(0), year(0) {};

    int getDay() const;

    void setDay(int day);

    int getMonth() const;

    void setMonth(int month);

    int getYear() const;

    void setYear(int year);
};



#endif //DATE_H
