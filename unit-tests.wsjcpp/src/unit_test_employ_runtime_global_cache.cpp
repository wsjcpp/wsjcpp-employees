#include "unit_test_employ_runtime_global_cache.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

REGISTRY_UNIT_TEST(UnitTestEmployRuntimeGlobalCache)

UnitTestEmployRuntimeGlobalCache::UnitTestEmployRuntimeGlobalCache()
    : WSJCppUnitTestBase("UnitTestEmployRuntimeGlobalCache") {
}

// ---------------------------------------------------------------------

void UnitTestEmployRuntimeGlobalCache::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestEmployRuntimeGlobalCache::run() {
    bool bTestSuccess = true;

    bool bResult = WSJCppEmployees::init({});
    compareB(bTestSuccess, "without-employ1", bResult, true);
    if (!bResult) {
        return bTestSuccess;
    }
    WJSCppEmployRuntimeGlobalCache *pCache = findWSJCppEmploy<WJSCppEmployRuntimeGlobalCache>();
    pCache->set("name1", "value3y2hf9f3h%%");
    compareB(bTestSuccess, "name1", pCache->has("name1"), true);
    if (pCache->has("name1")) {
        compareS(bTestSuccess, "name1-value", pCache->get("name1"), "value3y2hf9f3h%%");
    }
    compareB(bTestSuccess, "name2", pCache->has("name2"), false);
    WSJCppEmployees::deinit();
    return bTestSuccess;
}

