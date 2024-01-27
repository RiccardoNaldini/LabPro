#include "gtest/gtest.h"

#include "../Date.h"

TEST(Date, constructorTest){
    Date d(1, 1, 1);
    ASSERT_EQ(1, d.getDay());
    ASSERT_EQ(1, d.getMonth());
    ASSERT_EQ(1, d.getYear());
}

TEST(Date, setTest){
    Date d(1, 1, 1);

    d.setYear(1600);
    ASSERT_EQ(1600, d.getYear());

    d.setMonth(2);
    ASSERT_EQ(2, d.getMonth());

    d.setDay(29);
    ASSERT_EQ(29, d.getDay());


    //LANCI0 ECCEZIONI

    ASSERT_THROW(d.setDay(30), out_of_range);
    ASSERT_THROW(d.setDay(31), out_of_range);

    d.setDay(1);
    d.setYear(1400);
    ASSERT_THROW(d.setDay(29), out_of_range);
    ASSERT_THROW(d.setDay(30), out_of_range);
    ASSERT_THROW(d.setDay(31), out_of_range);

    d.setMonth(1);
    ASSERT_THROW(d.setDay(1311), out_of_range);

    d.setMonth(2);
    ASSERT_THROW(d.setDay(2212), out_of_range);

    d.setMonth(3);
    ASSERT_THROW(d.setDay(67), out_of_range);

    d.setMonth(4);
    ASSERT_THROW(d.setDay(31), out_of_range);

    d.setMonth(5);
    ASSERT_THROW(d.setDay(620), out_of_range);

    d.setMonth(6);
    ASSERT_THROW(d.setDay(31), out_of_range);

    d.setMonth(7);
    ASSERT_THROW(d.setDay(967), out_of_range);

    d.setMonth(8);
    ASSERT_THROW(d.setDay(98), out_of_range);

    d.setMonth(9);
    ASSERT_THROW(d.setDay(31), out_of_range);

    d.setMonth(10);
    ASSERT_THROW(d.setDay(10000), out_of_range);

    d.setMonth(11);
    ASSERT_THROW(d.setDay(31), out_of_range);

    d.setMonth(12);
    ASSERT_THROW(d.setDay(9999999), out_of_range);




}


TEST(Date, lesserTest){
    Date d1(30, 9, 2024);
    Date d2(29, 9, 2024);

    ASSERT_TRUE(d2<d1);

    d2.setDay(d1.getDay());
    d2.setMonth(8);
    ASSERT_TRUE(d2<d1);

    d2.setMonth(d1.getMonth());
    d2.setYear(2022);
    ASSERT_TRUE(d2<d1);


}

TEST(Date, greaterTest){
    Date d1(28, 2, 2024);
    Date d2(27, 2, 2024);

    ASSERT_TRUE(d1>d2);

    d2.setDay(d1.getDay());
    d2.setMonth(1);
    ASSERT_TRUE(d1>d2);

    d2.setMonth(d1.getMonth());
    d2.setYear(2022);
    ASSERT_TRUE(d1>d2);
}

TEST(Date, equalTest){
    Date d1(15, 7, 1916);
    Date d2(15, 7, 1916);

    ASSERT_TRUE(d1==d2);
}

TEST(Date, differentTest){
    Date d1(3, 5, 19);
    Date d2(19, 10, 2019);

    ASSERT_TRUE(d1!=d2);
}