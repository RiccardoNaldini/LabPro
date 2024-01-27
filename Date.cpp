#include "Date.h"
#include <iostream>
using namespace std;

void Date::checkDate(const int dd, const int mm, const int yy) const{
    bool leap = false;
    if(yy%4==0 or (yy%100==0 and yy%400==0))
        leap=true;

    //LANCIA ECCEZIONI QUANDO DATE INSERITE NON SONO VALIDE
    if(dd<1 || dd>31)
        throw out_of_range("Giorno inserito non valido");
    else if(mm<1 || mm>12)
        throw out_of_range("Mese inserito non valido");
    else{
        if(mm==2 and dd>29 and leap)
            throw out_of_range("Giorno non valido per Febbraio bisestile");
        if(mm==2 and dd > 28 and !leap)
            throw out_of_range("Giorno non valido per Febbraio non bisestile");
        if( (mm==4 || mm==6 || mm==9 || mm==11) and dd==31)
            throw out_of_range("Giorno 31 non valido per mesi di 30 giorni");
    }

}


Date::Date(const int dd, const int mm, const int yy) {
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

bool Date::operator>(const Date &right) const {
    bool greater = false;
    if(year > right.year)
        greater = true;
    else if(year == right.year) {
        if(month > right.month)
            greater = true;
        else if(month == right.month){
            if(day > right.day)
                greater = true;
        }
    }
    return greater;
}


bool Date::operator!=(const Date &right) const {
    bool different=false;
    if(day!=right.day || month!=right.month || year!=right.year)
        different=true;
    return different;
}