#include <iostream>
#include <map>
#include "Record.h"
#include "Date.h"

void Record::printDailyActivities(const Date& date) {
    date.printDate();

    for(auto const& activity:activities) {
        if (activity.first == date)
            cout << activity.second.getDescription() << " ||| " << activity.second.getStartingTime() << " --- "
                 << activity.second.getEndingTime() << endl;
        else
            continue;
    }
}

void Record::printRecord() {
    Date date = activities.begin()->first;
    date.printDate();

    for(auto const& activity:activities){
        if(activity.first!=date){
            cout << endl;
            date=activity.first;
            date.printDate();
        }
        cout << activity.second.getDescription() << " ||| " << activity.second.getStartingTime() << " --- " << activity.second.getEndingTime() << endl;
    }
}

vector<Activity> Record::getActivities(const Date &date) {
    vector<Activity> v;
    for(auto const& activity:activities)
        if(date == activity.first)
            v.push_back(activity.second);
    return v;
}

vector<Date> Record::getDates() {
    vector<Date> v;
    auto currentDate = Date(1,1,1);
    for(auto const& activity:activities){
        if(currentDate!=activity.first) {
            currentDate = activity.first;
            v.push_back(activity.first);
        }
    }
    sort(v.begin(), v.end());
    return v;
}

void Record::removeActivities(const Date &date) {
    auto begin = activities.find(date); //punta al primo elemento con chiave date
    unsigned size = activities.count(date);// numero di elementi con chiave date

    auto it = begin;
    while(size){               //cerca il puntatore all'ultimo elemento con chiave date
        it++;
        size--;
    }

    activities.erase(begin, it);     //elimina tutti gli elementi con chiave date

}


