#include "gtest/gtest.h"

#include "../Activity.h"

TEST(Activity, constructorTest){
    Date d(7, 07, 1348);
    Activity a("testing", "15:10", "15:11", d);
    ASSERT_EQ("testing", a.getDescription());
    ASSERT_EQ("15:10", a.getStartingTime());
    ASSERT_EQ("15:11", a.getEndingTime());
    ASSERT_EQ(d, a.getDate());
}

TEST(Activity, setTest){
    Date d(1, 1, 1);
    Activity a = Activity("", "", "", d);

    a.setDescription("testing");
    a.setStartingTime("15:12");
    a.setEndingTime("15:13");
    a.setDate(15, 9, 2200);

    ASSERT_EQ("testing", a.getDescription());
    ASSERT_EQ("15:12", a.getStartingTime());
    ASSERT_EQ("15:13", a.getEndingTime());
    ASSERT_EQ(15, a.getDate().getDay());
    ASSERT_EQ(9, a.getDate().getMonth());
    ASSERT_EQ(2200, a.getDate().getYear());
}