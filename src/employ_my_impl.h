#pragma once

#include "my_impl.h"
#include <wsjcpp_employees.h>

class EmployMyImpl : public WsjcppEmployBase, public IMyImpl, public IMyImpl2 {
public:
  EmployMyImpl();
  virtual bool init(const std::string &sName, bool bSilent) override;
  virtual bool deinit(const std::string &sName, bool bSilent) override;

  // IMyImpl
  virtual void doSomething() override;

  // IMyImpl2
  virtual void doSomething2() override;

private:
  std::string TAG;
};
