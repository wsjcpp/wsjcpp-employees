#include "unit_test_cicle_dependency.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

// ---------------------------------------------------------------------

class EmployCicle1 : public WsjcppEmployBase {
    public:
        EmployCicle1();
        static std::string name() { return "EmployCicle1"; };
        virtual bool init() override;
        virtual bool deinit() override;
    private:
        std::string TAG;
        std::string m_sValue;
};

// ---------------------------------------------------------------------

class EmployCicle2 : public WsjcppEmployBase {
    public:
        EmployCicle2();
        static std::string name() { return "EmployCicle2"; };
        virtual bool init() override;
        virtual bool deinit() override;
       
    private:
        std::string TAG;
        std::string m_sValue;
};

// ---------------------------------------------------------------------

class EmployCicle3 : public WsjcppEmployBase {
    public:
        EmployCicle3();
        static std::string name() { return "EmployCicle3"; };
        virtual bool init() override;
        virtual bool deinit() override;
    private:
        std::string TAG;
        std::string m_sValue;
};

// ---------------------------------------------------------------------

EmployCicle1::EmployCicle1() : WsjcppEmployBase(EmployCicle1::name(), {"unit-test-employ1", EmployCicle3::name()}) {
    TAG = EmployCicle1::name();
}

bool EmployCicle1::init() {
    m_sValue = "";
    return true;
}

bool EmployCicle1::deinit() {
    m_sValue = "";
    return true;
}

REGISTRY_WJSCPP_SERVICE_LOCATOR(EmployCicle1)

// ---------------------------------------------------------------------

EmployCicle2::EmployCicle2() : WsjcppEmployBase(EmployCicle2::name(), {"unit-test-employ1", EmployCicle1::name() }) {
    TAG = EmployCicle2::name();
}

bool EmployCicle2::init() {
    m_sValue = "";
    return true;
}

bool EmployCicle2::deinit() {
    m_sValue = "";
    return true;
}

REGISTRY_WJSCPP_SERVICE_LOCATOR(EmployCicle2)

// ---------------------------------------------------------------------

EmployCicle3::EmployCicle3() : WsjcppEmployBase(EmployCicle3::name(), {"unit-test-employ1", EmployCicle2::name() }) {
    TAG = EmployCicle3::name();
}

bool EmployCicle3::init() {
    m_sValue = "";
    return true;
}
bool EmployCicle3::deinit() {
    m_sValue = "";
    return true;
}

// REGISTRY_WJSCPP_SERVICE_LOCATOR(EmployCicle3)

// ---------------------------------------------------------------------

REGISTRY_WSJCPP_UNIT_TEST(UnitTestCicleDependency)

UnitTestCicleDependency::UnitTestCicleDependency()
    : WsjcppUnitTestBase("UnitTestCicleDependency") {
}

// ---------------------------------------------------------------------

bool UnitTestCicleDependency::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestCicleDependency::executeTest() {
    bool bTestSuccess = false;

    try {
        WsjcppEmployBase* pEmploy = new EmployCicle3();
        WsjcppEmployees::addService(EmployCicle3::name(), pEmploy);
    } catch(const std::exception &e) {
        std::string sErrorMsg(e.what());
        if (sErrorMsg == "Cicle dependency: EmployCicle3 -> EmployCicle2 -> EmployCicle1 -> EmployCicle3") {
            bTestSuccess = true;
        }
    }
    compare("Expected specific exception", bTestSuccess, true);
}

// ---------------------------------------------------------------------

bool UnitTestCicleDependency::doAfterTest() {
    // nothing
    return true;
}
