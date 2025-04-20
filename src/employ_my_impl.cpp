
#include "employ_my_impl.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// EmployMyImpl

REGISTRY_WJSCPP_SERVICE_LOCATOR(EmployMyImpl)

EmployMyImpl::EmployMyImpl()
: WsjcppEmployBase({IMyImpl::name(), IMyImpl2::name()}, {}) {
    TAG = "EmployMyImpl";
}

bool EmployMyImpl::init() {
    WsjcppLog::info(TAG, "init");
    return true;
}

bool EmployMyImpl::deinit() {
    WsjcppLog::info(TAG, "deinit");
    return true;
}

void EmployMyImpl::doSomething() {
    WsjcppLog::info(TAG, "doSomething");
}

void EmployMyImpl::doSomething2() {
    WsjcppLog::info(TAG, "doSomething2");
}

