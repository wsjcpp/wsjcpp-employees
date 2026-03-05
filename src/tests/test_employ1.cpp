/**********************************************************************************
 * Copyright (c) 2020-2026 Evgenii Sopov <mrseakg@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ***********************************************************************************/

// Original repository: https://github.com/wsjcpp/wsjcpp-employees

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