#include <string>
#include <utility>
#include<map>
#include <vector>
#include<algorithm>
#include <iostream>
#include "Activity.h"

using namespace std;


#ifndef UNTITLED_REGISTRO_H
#define UNTITLED_REGISTRO_H

class Register {
public:
    Register()=default;
    ~Register()=default;


    void addActivity(const Activity& a) {activities.insert(make_pair(a.getDate(), a));}


    vector<Activity> getActivities(const Date& date) const;
    vector<Activity> getAllActivities() const;
    vector <Date> getDates() const;

    bool removeActivities(const Date& date);



private:
    multimap<Date, Activity> activities;
};


#endif //UNTITLED_REGISTRO_H
