#include<iostream>
using namespace std;

#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

class Date{
private:
    int day;
    int month;
    int year;
    void checkDate(const int& dd, const int& mm, const int& yy);

public:
    Date(const int& dd, const int& mm, const int& yy);
    ~Date()=default;

    void setDay(const int& dd){
        checkDate(dd, this->month, this->year);
        day=dd;
    }
    void setMonth(const int& mm){
        checkDate(this->day, mm, this->year);
        month=mm;
    }
    void setYear(const int& yy){
        checkDate(this->day, this->month, yy);
        year=yy;
    }

    const int& getDay(){return day;}
    const int& getMonth(){return month;}
    const int& getYear(){return year;}

    void printDate() const{
        cout << day << "/" << month << "/" << year << endl;
    }

    bool operator< (const Date& right) const;
    bool operator> (const Date& right) const;
    bool operator== (const Date& right) const;
    bool operator!= (const Date& right) const;


};


#endif //UNTITLED_DATE_H

