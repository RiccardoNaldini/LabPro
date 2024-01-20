#include "gtest/gtest.h"

#include "../Activity.h"

TEST(Activity, constructorTest){
    Activity a = Activity("testing", "15:10", "15:11");
    ASSERT_EQ("testing", a.getDescription());
    ASSERT_EQ("15:10", a.getStartingTime());
    ASSERT_EQ("15:11", a.getEndingTime());
}

TEST(Activity, setTest){
    Activity a = Activity("", "", "");

    a.setDescription("testing");
    a.setStartingTime("15:12");
    a.setEndingTime("15:13");

    ASSERT_EQ("testing", a.getDescription());
    ASSERT_EQ("15:12", a.getStartingTime());
    ASSERT_EQ("15:13", a.getEndingTime());
}