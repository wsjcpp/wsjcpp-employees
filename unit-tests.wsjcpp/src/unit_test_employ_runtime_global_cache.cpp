#include "unit_test_employ_runtime_global_cache.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestEmployRuntimeGlobalCache)

UnitTestEmployRuntimeGlobalCache::UnitTestEmployRuntimeGlobalCache()
    : WsjcppUnitTestBase("UnitTestEmployRuntimeGlobalCache") {
}

// ---------------------------------------------------------------------

bool UnitTestEmployRuntimeGlobalCache::doBeforeTest() {
    return WsjcppEmployees::init({});
}

// ---------------------------------------------------------------------

void UnitTestEmployRuntimeGlobalCache::executeTest() {
    WsjcppEmployRuntimeGlobalCache *pCache = findWsjcppEmploy<WsjcppEmployRuntimeGlobalCache>();
    pCache->set("name1", "value3y2hf9f3h%%");
    compare("name1", pCache->has("name1"), true);
    if (pCache->has("name1")) {
        compare("name1-value", pCache->get("name1"), "value3y2hf9f3h%%");
    }
    compare("name2", pCache->has("name2"), false);
}

// ---------------------------------------------------------------------

bool UnitTestEmployRuntimeGlobalCache::doAfterTest() {
    WsjcppEmployees::deinit();
    return true;
}