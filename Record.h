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

class Record  {
public:
    Record(const Date& date, const Activity& a){
        activities.insert(make_pair(date, a));
    }

    ~Record()=default;


    void addActivity(const Date& date, const Activity& a) {activities.insert(make_pair(date, a));}


    vector<Activity> getActivities(const Date& date);
    vector <Date> getDates();

    void removeActivities(const Date& date);


    void printDailyActivities(const Date& date);
    void printRecord();


private:
    multimap<Date, Activity> activities;
};


#endif //UNTITLED_REGISTRO_H
