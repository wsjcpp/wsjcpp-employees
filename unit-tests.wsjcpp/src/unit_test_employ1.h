#ifndef UNIT_TEST_EMPLOY1_H
#define UNIT_TEST_EMPLOY1_H

#include <wsjcpp_unit_tests.h>

class UnitTestEmploy1 : public WsjcppUnitTestBase {
    public:
        UnitTestEmploy1();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_EMPLOY1_H

