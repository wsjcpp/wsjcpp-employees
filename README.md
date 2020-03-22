# wsjcpp-employees

[![Build Status](https://api.travis-ci.org/wsjcpp/wsjcpp-employees.svg?branch=master)](https://travis-ci.org/wsjcpp/wsjcpp-employees) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-employees.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-employees/stargazers) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-employees.svg)](https://github.com/wsjcpp/wsjcpp-employees/) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-employees.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-employees/network/members)

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

For init you must call `WSJCppEmployees::init({})`

Example main func:
```
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    if (!WSJCppCore::dirExists(".logs")) {
        WSJCppCore::makeDir(".logs");
    }
    WSJCppLog::setPrefixLogFile("wsjcpp-employees");
    WSJCppLog::setLogDirectory(".logs");
    
    // init employees
    if (!WSJCppEmployees::init({})) {
        WSJCppLog::err(TAG, "Could not init employees");
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
    WJSCppEmployRuntimeGlobalCache *pCache = findWSJCppEmploy<WJSCppEmployRuntimeGlobalCache>();
    pCache->set("name", "value");
}
```

### Example of define you employ (simple)

(don't foget add to build)

Example Header `your_employ.h`:
```
#ifndef WSJCPP_EMPLOYEES_H
#define WSJCPP_EMPLOYEES_H

#include <wsjcpp_employees.h>

class YourEmploy : public WSJCppEmployBase {
    public:
        YourEmploy();
        static std::string name() { return "YourEmploy"; }
        virtual bool init() override;
        void doSomething();
    private:
        std::string TAG;
};

#endif // WSJCPP_EMPLOYEES_H
```

Example source-code `your_employ.cpp`:
```
#include "your_employ.h"

REGISTRY_WJSCPP_EMPLOY(YourEmploy)

YourEmploy::YourEmploy()
    : WSJCppEmployBase(YourEmploy::name(), {}) {
    TAG = YourEmploy::name();
}

void YourEmploy::doSomething() {
    WSJCppLog::info(TAG, "doSomething called");
}
```

Now you can call you method for employ

```
#inluce <your_employ.h>

void someFunc() {
    YourEmploy *pYourEmploy = findWSJCppEmploy<YourEmploy>();
    pYourEmploy->doSomething();
}
```




