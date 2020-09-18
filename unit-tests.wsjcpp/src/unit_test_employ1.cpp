#include "unit_test_employ1.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

// ---------------------------------------------------------------------


class Employ1 : public WsjcppEmployBase {
    public:
        Employ1();
        static std::string name() { return "Employ1"; };
        virtual bool init() override;
        virtual bool deinit() override;

        void set(const std::string &sValue);
        std::string get();
    private:
        std::string TAG;
        std::string m_sValue;
};

REGISTRY_WJSCPP_SERVICE_LOCATOR(Employ1)

Employ1::Employ1() 
    : WsjcppEmployBase(Employ1::name(), {"unit-test-employ1"}) {
    TAG = Employ1::name();
}

// ---------------------------------------------------------------------

bool Employ1::init() {
    m_sValue = "";
    return true;
}

// ---------------------------------------------------------------------

bool Employ1::deinit() {
    m_sValue = "";
    return true;
}

// ---------------------------------------------------------------------

void Employ1::set(const std::string &sValue) { 
    m_sValue = sValue;
};

// ---------------------------------------------------------------------

std::string Employ1::get() {
    return m_sValue;
}

// ---------------------------------------------------------------------

REGISTRY_WSJCPP_UNIT_TEST(UnitTestEmploy1)

UnitTestEmploy1::UnitTestEmploy1()
    : WsjcppUnitTestBase("UnitTestEmploy1") {
}

// ---------------------------------------------------------------------

bool UnitTestEmploy1::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestEmploy1::executeTest() {
    bool bTestSuccess = true;

    WsjcppLog::warn(TAG, "init alone employees");
    bool bResult = WsjcppEmployees::init({});
    compare("without-employ1", bResult, true);
    if (!bResult) {
        return;
    }
    WsjcppEmployRuntimeGlobalCache *pCache = findWsjcppEmploy<WsjcppEmployRuntimeGlobalCache>();
    WsjcppEmployees::deinit();

    // start new 

    bResult = WsjcppEmployees::init({"unit-test-employ1"});
    compare("unit-test-employ1", bResult, true);
    if (!bResult) {
        return;
    }

    Employ1 *pEmploy1 = findWsjcppEmploy<Employ1>();

    pEmploy1->set("test4562132");
    compare("value", pEmploy1->get(), "test4562132");

    WsjcppEmployees::deinit();
}

// ---------------------------------------------------------------------

bool UnitTestEmploy1::doAfterTest() {
    // nothing
    return true;
}