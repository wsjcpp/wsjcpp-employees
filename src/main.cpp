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

#include "my_impl.h"
#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

class EmployeesLogger : public IWsjcppEmployeesLogger {
public:
  virtual void info(const std::string &tag, const std::string &message) override {
    WsjcppLog::info(tag, message);
  }

  virtual void ok(const std::string &tag, const std::string &message) override {
    WsjcppLog::ok(tag, message);
  }

  virtual void warn(const std::string &tag, const std::string &message) override {
    WsjcppLog::warn(tag, message);
  }

  virtual void err(const std::string &tag, const std::string &message) override {
    WsjcppLog::err(tag, message);
  }

  virtual void throw_err(const std::string &tag, const std::string &message) override {
    WsjcppLog::throw_err(tag, message);
  }
};


int main(int argc, const char *argv[]) {
  std::string TAG = "MAIN";
  std::string appName = std::string(WSJCPP_APP_NAME);
  std::string appVersion = std::string(WSJCPP_APP_VERSION);
  if (!wsjcpp::dir_exists(".logs")) {
    WsjcppCore::makeDir(".logs");
  }
  WsjcppLog::setPrefixLogFile("wsjcpp-employees");
  WsjcppLog::setLogDirectory(".logs");
  WsjcppEmployees::setLogger(new EmployeesLogger());

  WsjcppEmployeesInit empls({});
  if (!empls.initialized) {
    WsjcppLog::err(TAG, "Could not init employees");
    return -1;
  }

  auto *p1 = findWsjcppEmploy<IMyImpl>();
  p1->doSomething();

  auto *p2 = findWsjcppEmploy<IMyImpl2>();
  p2->doSomething2();

  // TODO your code here
  return 0;
}
