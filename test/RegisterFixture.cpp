#include "gtest/gtest.h"

#include "../Register.h"


class RegisterSuite : public ::testing::Test {

protected:
    Register r;
    virtual void SetUp() {
        Date d1(27, 1, 2024);
        Date d2(23, 3, 1965);
        Activity a1("testOne", "15:24", "15:25", d1);
        Activity a2("testTwo", "15:26", "15:27", d1);
        Activity a3("testThree", "16:58", "17:01", d2);

        r.addActivity(a1);
        r.addActivity(a2);
        r.addActivity(a3);
    }


};


TEST_F(RegisterSuite, TestRemove) {
    Date d1(17, 05, 2002);
    Date d2(27, 1, 2024);
    bool f = r.removeActivities(d1);    //data d1 non presente in Register
    bool t = r.removeActivities(d2);    //data d2 presente in register

    ASSERT_FALSE(f);
    ASSERT_TRUE(t);

    auto acts = r.getAllActivities();
    ASSERT_EQ(acts.size(), 1);

}

TEST_F(RegisterSuite, TestAdd){
    auto acts1 = r.getAllActivities();
    Date d(19, 9, 1919);
    Activity a("testAdd", "15:50", "15:52", d);
    r.addActivity(a);
    auto acts2 = r.getAllActivities();
    int size1 = acts1.size();
    int size2 = acts2.size();
    ASSERT_EQ(size1, --size2);
}

