#include <vector>
#include <iostream>
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

class Employ1 : public WsjcppEmployBase {
    public:
        Employ1();
        static std::string name() { return "Employ1"; };
        virtual bool init(const std::string &sName, bool bSilent) override;
        virtual bool deinit(const std::string &sName, bool bSilent) override;

        void set(const std::string &sValue);
        std::string get();
    private:
        std::string TAG;
        std::string m_sValue;
};

REGISTRY_WSJCPP_EMPLOY(Employ1)

Employ1::Employ1()
    : WsjcppEmployBase({Employ1::name()}, {"unit-test-employ1"}) {
    TAG = Employ1::name();
}

bool Employ1::init(const std::string &sName, bool bSilent) {
    m_sValue = "";
    return true;
}

bool Employ1::deinit(const std::string &sName, bool bSilent) {
    m_sValue = "";
    return true;
}

// ---------------------------------------------------------------------

void Employ1::set(const std::string &sValue) {
    m_sValue = sValue;
};

std::string Employ1::get() {
    return m_sValue;
}

int main() {
    std::cout << "init alone employees" << std::endl;
    bool bResult = WsjcppEmployees::init({});
    if (!bResult) {
        return -1;
    }
    WsjcppEmployRuntimeGlobalCache *pCache = findWsjcppEmploy<WsjcppEmployRuntimeGlobalCache>();
    WsjcppEmployees::deinit();

    // start new
    bResult = WsjcppEmployees::init({"unit-test-employ1"});
    if (!bResult) {
        return -1;
    }

    Employ1 *pEmploy1 = findWsjcppEmploy<Employ1>();

    pEmploy1->set("test4562132");
    if (pEmploy1->get() != "test4562132") {
        return -1;
    }

    WsjcppEmployees::deinit();
    return 0;
}