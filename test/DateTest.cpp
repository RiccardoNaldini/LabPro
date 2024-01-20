#include "gtest/gtest.h"

#include "../Date.h"

TEST(Date, constructorTest){
    Date d = Date(1, 1, 1);
    ASSERT_EQ(1, d.getDay());
    ASSERT_EQ(1, d.getMonth());
    ASSERT_EQ(1, d.getYear());
}

TEST(Date, setTest){
    Date d = Date(1, 1, 1);

    d.setDay(12);
    ASSERT_EQ(12, d.getDay());

    d.setMonth(11);
    ASSERT_EQ(11, d.getMonth());

    d.setYear(2023);
    ASSERT_EQ(2023, d.getYear());
}


TEST(Date, lesserTest){
    Date d1 = Date(30, 9, 2024);
    Date d2 = Date(29, 9, 2024);

    ASSERT_TRUE(d2<d1);

    d2.setDay(d1.getDay());
    d2.setMonth(8);
    ASSERT_TRUE(d2<d1);

    d2.setMonth(d1.getMonth());
    d2.setYear(2022);
    ASSERT_TRUE(d2<d1);
}

TEST(Date, greaterTest){
    Date d1 = Date(28, 2, 2024);
    Date d2 = Date(27, 2, 2024);

    ASSERT_TRUE(d1>d2);

    d2.setDay(d1.getDay());
    d2.setMonth(1);
    ASSERT_TRUE(d1>d2);

    d2.setMonth(d1.getMonth());
    d2.setYear(2022);
    ASSERT_TRUE(d1>d2);
}

TEST(Date, equalTest){
    Date d1 = Date(15, 7, 1916);
    Date d2 = Date(15, 7, 1916);

    ASSERT_TRUE(d1==d2);
}

TEST(Date, differentTest){
    Date d1 = Date(3, 5, 19);
    Date d2 = Date(19, 10, 2019);

    ASSERT_TRUE(d1!=d2);
}