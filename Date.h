#include<iostream>

using namespace std;

#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

class Date {
private:
    int day;
    int month;
    int year;

    void checkDate(int dd, int mm, int yy) const;

public:
    Date(int dd, int mm, int yy);

    ~Date() = default;

    void setDay(const int dd) {
        checkDate(dd, month, year);
        day = dd;
    }

    void setMonth(const int mm) {
        checkDate(day, mm, year);
        month = mm;
    }

    void setYear(const int yy) {
        checkDate(day, month, yy);
        year = yy;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }



    bool operator<(const Date &right) const;
    bool operator>(const Date &right) const;
    bool operator==(const Date &right) const;
    bool operator!=(const Date &right) const;


};


#endif //UNTITLED_DATE_H

