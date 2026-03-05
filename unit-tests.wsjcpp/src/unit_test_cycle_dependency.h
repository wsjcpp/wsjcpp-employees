#ifndef UNIT_TEST_CYCLE_DEPENDENCY_H
#define UNIT_TEST_CYCLE_DEPENDENCY_H

#include <wsjcpp_unit_tests.h>

class UnitTestCycleDependency : public WsjcppUnitTestBase {
    public:
        UnitTestCycleDependency();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_CYCLE_DEPENDENCY_H

