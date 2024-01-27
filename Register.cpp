#include "Register.h"
#include "Date.h"


vector<Activity> Register::getActivities(const Date &date) const{
    vector<Activity> v;
    for(auto const& activity:activities)
        if(date == activity.first)
            v.push_back(activity.second);
    return v;
}

vector<Date> Register::getDates() const{
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

bool Register::removeActivities(const Date &date) {
    auto begin = activities.find(date); //punta al primo elemento con chiave date
    int numDate = activities.count(date);// numero di elementi con chiave date
    int size = activities.size();
    bool removed = false;

    auto it = begin;
    while(numDate){               //cerca il puntatore all'ultimo elemento con chiave date
        it++;
        numDate--;
    }

    activities.erase(begin, it);     //elimina tutti gli elementi con chiave date

    int checkSize = activities.size();

    if(checkSize < size)
        removed = true;

    return removed;
}

vector<Activity> Register::getAllActivities() const {
    vector<Activity> v;
    for(auto const& activity:activities)
        v.push_back(activity.second);
    return v;
}




