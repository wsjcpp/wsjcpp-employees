# wsjcpp-employees

[![Build Status](https://api.travis-ci.org/wsjcpp/wsjcpp-employees.svg?branch=master)](https://travis-ci.org/wsjcpp/wsjcpp-employees) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-employees.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-employees/stargazers) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-employees.svg)](https://github.com/wsjcpp/wsjcpp-employees/) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-employees.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-employees/network/members) [![Total alerts](https://img.shields.io/lgtm/alerts/g/wsjcpp/wsjcpp-employees.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-employees/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wsjcpp/wsjcpp-employees.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-employees/context:cpp)

C++ classes for service-architecture

## How to integrate to your project

via wsjcpp:
```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-employees:master
```

or include this files:

- src.wsjcpp/wsjcpp_core/wsjcpp_core.h
- src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp
- src/wsjcpp_employees.h
- src/wsjcpp_employees.cpp

## How use this

For init you must call `WsjcppEmployees::init({})`

Example main func:
```
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    if (!WsjcppCore::dirExists(".logs")) {
        WsjcppCore::makeDir(".logs");
    }
    WsjcppLog::setPrefixLogFile("wsjcpp-employees");
    WsjcppLog::setLogDirectory(".logs");

    // init employees
    bool bSilent = false;
    WsjcppEmployeesInit empls({}, bSilent);
    if (!empls.inited) {
        WsjcppLog::err(TAG, "Could not init employees");
        return -1;
    }
    return 0;
}
```

Example output:
```
% ./wsjcpp-employees
2020-03-22 11:32:31.750, 0x0x110c21dc0 [INFO] WJSCppEmployRuntimeGlobalCache: init
2020-03-22 11:32:31.750, 0x0x110c21dc0 [OK] Employees_init: Init WJSCppEmployRuntimeGlobalCache ... OK
```

Now you can call from any place:
```
#inluce <wsjcpp_employees.h>

void someFunc() {
    WJSCppEmployRuntimeGlobalCache *pCache = findWsjcppEmploy<WJSCppEmployRuntimeGlobalCache>();
    pCache->set("name", "value");
}
```

### Example of define you employ use a wsjcpp

```sh
$ wsjcpp gen WsjcppEmploy MyImpl
```

And will be generated several files:
Example Header with interface `src/my_impl.h`:
```cpp
#ifndef MY_IMPL_H
#define MY_IMPL_H

#include <string>

class IMyImpl {
    public:
        static std::string name() { return "IMyImpl"; }
        virtual void doSomething() = 0;
};

#endif // MY_IMPL_H
```

Example Header `src/employ_my_impl.h`:
```cpp
#ifndef EMPLOY_MY_IMPL_H
#define EMPLOY_MY_IMPL_H

#include <wsjcpp_employees.h>
#include "my_impl.h"

class EmployMyImpl : public WsjcppEmployBase, public IMyImpl {
    public:
        EmployMyImpl();
        virtual bool init(const std::string &sName, bool bSilent) override;
        virtual bool deinit(const std::string &sName, bool bSilent) override;

        // IMyImpl
        virtual void doSomething() override;

    private:
        std::string TAG;
};

#endif // EMPLOY_MY_IMPL_H
```

Example source-code `src/employ_my_impl.cpp`:
```cpp
#include "employ_my_impl.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------
// EmployMyImpl

REGISTRY_WJSCPP_SERVICE_LOCATOR(EmployMyImpl)

EmployMyImpl::EmployMyImpl()
: WsjcppEmployBase({IMyImpl::name()}, {}) {
    TAG = "EmployMyImpl";
}

bool EmployMyImpl::init(const std::string &sName, bool bSilent) {
    if (!bSilent) {
        WsjcppLog::info(TAG, "init " + sName);
    }
    return true;
}

bool EmployMyImpl::deinit(const std::string &sName, bool bSilent) {
    if (!bSilent) {
        WsjcppLog::info(TAG, "deinit " + sName);
    }
    return true;
}

void EmployMyImpl::doSomething() {
    WsjcppLog::info(TAG, "doSomething");
}
```

1. If you created manually: don't foget add to build
2. For call ::init you must call `WsjcppEmployees::init({})` in main function or use a helper class `WsjcppEmployeesInit`
3. find employ and call you method from any place

```cpp
#inluce <your_employ.h>

void someFunc() {
    YourEmploy *pYourEmploy = findWsjcppEmploy<YourEmploy>();
    pYourEmploy->doSomething();
}

void main() {
    ...
    WsjcppEmployeesInit empls({});
    someFunc();
}
```

## Initialization employees in order

1. Second employ required init after first

```cpp

// second - will be init after
SecondEmploy::SecondEmploy()
    : WsjcppEmployBase(SecondEmploy::name(), {"FirstEmploy"}) {
    TAG = SecondEmploy::name();
}

bool SecondEmploy::init(const std::string &sName, bool bSilent) {
    // will be called second
}

// first employ - will be init every time
FirstEmploy::FirstEmploy()
    : WsjcppEmployBase(FirstEmploy::name(), {}) {
    TAG = FirstEmploy::name();
}

bool SecondEmploy::init(const std::string &sName, bool bSilent) {
    // will be called first
}
```
Why it can be need? For init some connections or cache data.
For example, you wanna load some data from database

UsersEmploy
 - after: DatabaseEmploy

* In DatabaseEmploy::init you can check connection to database and do migration database struct
* In UsersEmploy::init you can use DatabaseEmploy for load user's tokens on server start

2. You wanna init fork some employs

Also you can define on init:
```cpp
WsjcppEmployees::init({"server-start"});
```
or same with `WsjcppEmployeesInit`
```cpp
WsjcppEmployeesInit empls({"server-start"});
```
So it will be call "::init" employees only there which has this requirements.

