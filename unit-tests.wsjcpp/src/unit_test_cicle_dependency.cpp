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

class IEmployCicle3 {
    public:
        static std::string name() { return "IEmployCicle3"; };
        virtual void cicle3() = 0;
};

class EmployCicle3 : public WsjcppEmployBase, public IEmployCicle3 {
    public:
        EmployCicle3();
        virtual bool init() override;
        virtual bool deinit() override;

        // IEmployCicle3
        virtual void cicle3() override {};
    private:
        std::string TAG;
        std::string m_sValue;
};

// ---------------------------------------------------------------------

EmployCicle1::EmployCicle1() : WsjcppEmployBase({EmployCicle1::name()}, {"unit-test-employ1", EmployCicle3::name()}) {
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

EmployCicle2::EmployCicle2() : WsjcppEmployBase({EmployCicle2::name()}, {"unit-test-employ1", EmployCicle1::name() }) {
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

EmployCicle3::EmployCicle3() : WsjcppEmployBase({IEmployCicle3::name()}, {"unit-test-employ1", EmployCicle2::name() }) {
    TAG = IEmployCicle3::name();
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
        REGISTRY_WJSCPP_SERVICE_LOCATOR(EmployCicle3)
        // WsjcppEmployBase* pEmploy = new ();
        // WsjcppEmployees::addEmploy(EmployCicle3::name(), pEmploy);
    } catch(const std::exception &e) {
        std::string sErrorMsg(e.what());
        if (sErrorMsg == "Cicle dependency: IEmployCicle3 -> EmployCicle2 -> EmployCicle1 -> IEmployCicle3") {
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
