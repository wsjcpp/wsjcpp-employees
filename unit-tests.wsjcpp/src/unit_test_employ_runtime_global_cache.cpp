#include "unit_test_employ_runtime_global_cache.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestEmployRuntimeGlobalCache)

UnitTestEmployRuntimeGlobalCache::UnitTestEmployRuntimeGlobalCache()
    : WsjcppUnitTestBase("UnitTestEmployRuntimeGlobalCache") {
}

// ---------------------------------------------------------------------

void UnitTestEmployRuntimeGlobalCache::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestEmployRuntimeGlobalCache::run() {
    bool bTestSuccess = true;

    bool bResult = WsjcppEmployees::init({});
    compareB(bTestSuccess, "without-employ1", bResult, true);
    if (!bResult) {
        return bTestSuccess;
    }
    WJSCppEmployRuntimeGlobalCache *pCache = findWsjcppEmploy<WJSCppEmployRuntimeGlobalCache>();
    pCache->set("name1", "value3y2hf9f3h%%");
    compareB(bTestSuccess, "name1", pCache->has("name1"), true);
    if (pCache->has("name1")) {
        compareS(bTestSuccess, "name1-value", pCache->get("name1"), "value3y2hf9f3h%%");
    }
    compareB(bTestSuccess, "name2", pCache->has("name2"), false);
    WsjcppEmployees::deinit();
    return bTestSuccess;
}

