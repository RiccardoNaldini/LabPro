#include <string>
using namespace std;

#ifndef UNTITLED_ATTIVITÀ_H
#define UNTITLED_ATTIVITÀ_H

class Activity{
public:
    Activity(string d, string st, string en):description(std::move(d)), startingTime(std::move(st)), endingTime(std::move(en)){}

    ~Activity()= default;

    void setDescription(const string& d) {description=d;}
    void setStartingTime(const string& st) {startingTime=st;}
    void setEndingTime(const string& en) {endingTime=en;}

    const string& getDescription() const {return description;}
    const string& getStartingTime() const {return startingTime;}
    const string& getEndingTime() const {return endingTime;}



private:
    string description;
    string startingTime;
    string endingTime;

};
#endif //UNTITLED_ATTIVITÀ_H
