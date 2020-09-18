#ifndef UNIT_TEST_CICLE_DEPENDENCY_H
#define UNIT_TEST_CICLE_DEPENDENCY_H

#include <wsjcpp_unit_tests.h>

class UnitTestCicleDependency : public WsjcppUnitTestBase {
    public:
        UnitTestCicleDependency();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_CICLE_DEPENDENCY_H

