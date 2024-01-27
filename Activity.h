#include <string>
#include "Date.h"
using namespace std;

#ifndef UNTITLED_ATTIVITÀ_H
#define UNTITLED_ATTIVITÀ_H

class Activity{
public:
    Activity(string d, string st, string en, const Date& dt):description(std::move(d)), startingTime(std::move(st)), endingTime(std::move(en)), date(dt){}

    ~Activity()= default;

    void setDescription(const string& d) {description=d;}
    void setStartingTime(const string& st) {startingTime=st;}
    void setEndingTime(const string& en) {endingTime=en;}
    void setDate(const Date& dt) {date=dt;}

    const string& getDescription() const {return description;}
    const string& getStartingTime() const {return startingTime;}
    const string& getEndingTime() const {return endingTime;}
    const Date& getDate() const {return date;}



    bool operator== (const Activity& right) const{
        bool equal=false;
        if(description==right.description and startingTime==right.startingTime and endingTime==right.endingTime and date==right.date)
            equal=true;
        return equal;
    }

private:
    string description;
    string startingTime;
    string endingTime;
    Date date;

};
#endif //UNTITLED_ATTIVITÀ_H
