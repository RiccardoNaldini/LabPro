#include <string>
#include <utility>
#include<map>
#include <vector>
#include<algorithm>
#include <iostream>
#include "Activity.h"
#include "Date.h"
using namespace std;


#ifndef UNTITLED_REGISTRO_H
#define UNTITLED_REGISTRO_H

class Register {
public:
    Register(const Date& date, const Activity& a){
        activities.insert(make_pair(date, a));
    }

    ~Register()=default;


    void addActivity(const Date& date, const Activity& a) {activities.insert(make_pair(date, a));}


    vector<Activity> getActivities(const Date& date) const;
    vector <Date> getDates() const;

    bool removeActivities(const Date& date);



private:
    multimap<Date, Activity> activities;
};


#endif //UNTITLED_REGISTRO_H
