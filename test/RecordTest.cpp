#include "gtest/gtest.h"

#include "../Register.h"



TEST(Record, constructorTest){
Date d(1, 1, 1);
Activity a("default", "default", "default");
Agenda r(d, a);

auto acts = r.getActivities(d);
auto dates = r.getDates();

ASSERT_EQ(d.getDay(), dates[0].getDay());
ASSERT_EQ(d.getMonth(), dates[0].getMonth());
ASSERT_EQ(d.getYear(), dates[0].getYear());


ASSERT_EQ(a, acts[0]);
}

TEST(Record, addingTest){
    Date d = Date(1, 1, 1);
    Activity a1 = Activity("default", "default", "default");
    Agenda r = Agenda(d, a1);

    auto a2 = Activity("addingTest", "17:58", "17:59");

    r.addActivity(d, a2);
    auto acts =  r.getActivities(d);

    ASSERT_EQ(a1, acts[0]);
    ASSERT_EQ(a2, acts[1]);

}

TEST(Record, removingTest){
    Date d1 = Date(1, 1, 1);
    Activity a1 = Activity("default", "default", "default");
    Agenda r = Agenda(d1, a1);

    auto d2 = Date(20, 01, 2024);
    auto a2 = Activity("removingTest", "17:58", "17:59");
    auto a3 = Activity("removingTest.1", "18:11", "18:12");

    r.addActivity(d2, a2);
    r.addActivity(d1, a3);
    r.removeActivities(d1);

    auto dates = r.getDates();
    auto acts = r.getActivities(dates[0]);

    ASSERT_EQ(d2, dates[0]);
    ASSERT_EQ(a2, acts[0]); 
}
