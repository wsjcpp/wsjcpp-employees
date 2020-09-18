#ifndef UNIT_TEST_EMPLOY_RUNTIME_GLOBAL_CACHE_H
#define UNIT_TEST_EMPLOY_RUNTIME_GLOBAL_CACHE_H

#include <wsjcpp_unit_tests.h>

class UnitTestEmployRuntimeGlobalCache : public WsjcppUnitTestBase {
    public:
        UnitTestEmployRuntimeGlobalCache();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_EMPLOY_RUNTIME_GLOBAL_CACHE_H

