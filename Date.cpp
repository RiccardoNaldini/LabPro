#include "Date.h"
#include <iostream>
using namespace std;

void Date::checkDate(const int &dd, const int &mm, const int &yy) {
    bool leap = false;
    if(yy%4==0)
        leap=true;

    //LANCIA ECCEZIONI QUANDO DATE INSERITE NON SONO VALIDE
    if(dd<1 || dd>31)
        throw out_of_range("Not a valid day inserted");
    else if(mm<1 || mm>12)
        throw out_of_range("Not a valid month inserted");
    else{
        if(mm==2 and dd>29 and leap)
            throw out_of_range("Invalid day for February on leap years");
        if(mm==2 and dd > 28 and !leap)
            throw out_of_range("Invalid day for February on not-leap years");
        if( (mm==4 || mm==6 || mm==9 || mm==11) and dd==31)
            throw out_of_range("31th is not a valid day for a 30-days month");
    }

}


Date::Date(const int &dd, const int &mm, const int &yy) {
    checkDate(dd, mm, yy);
    day=dd;
    month=mm;
    year=yy;
}

bool Date::operator<(const Date &right) const {
    bool lesser= false;
    if(year < right.year)
        lesser = true;
    else if(year == right.year) {
        if(month < right.month)
            lesser = true;
        else if(month == right.month){
            if(day < right.day)
                lesser = true;
        }
    }
    return lesser;
}

bool Date::operator==(const Date &right) const {
    bool equal=false;
    if(day==right.day and month==right.month and year==right.year)
        equal=true;
    return equal;
}
