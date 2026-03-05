#include <vector>
#include <wsjcpp_employees.h>

// ---------------------------------------------------------------------

class EmployCycle1 : public WsjcppEmployBase {
public:
  EmployCycle1();
  static std::string name() { return "EmployCycle1"; };
  virtual bool init(const std::string &sName, bool bSilent) override;
  virtual bool deinit(const std::string &sName, bool bSilent) override;
private:
  std::string TAG;
  std::string m_sValue;
};

// ---------------------------------------------------------------------

class EmployCycle2 : public WsjcppEmployBase {
public:
  EmployCycle2();
  static std::string name() { return "EmployCycle2"; };
  virtual bool init(const std::string &sName, bool bSilent) override;
  virtual bool deinit(const std::string &sName, bool bSilent) override;
private:
  std::string TAG;
  std::string m_sValue;
};

// ---------------------------------------------------------------------

class IEmployCycle3 {
public:
  static std::string name() { return "IEmployCycle3"; };
  virtual void cycle3() = 0;
};

class EmployCycle3 : public WsjcppEmployBase, public IEmployCycle3 {
public:
  EmployCycle3();
  virtual bool init(const std::string &sName, bool bSilent) override;
  virtual bool deinit(const std::string &sName, bool bSilent) override;

  // IEmployCycle3
  virtual void cycle3() override {};
private:
  std::string TAG;
  std::string m_sValue;
};

// ---------------------------------------------------------------------

EmployCycle1::EmployCycle1() : WsjcppEmployBase({EmployCycle1::name()}, {"unit-test-employ1", EmployCycle3::name()}) {
  TAG = EmployCycle1::name();
}

bool EmployCycle1::init(const std::string &sName, bool bSilent) {
  m_sValue = "";
  return true;
}

bool EmployCycle1::deinit(const std::string &sName, bool bSilent) {
  m_sValue = "";
  return true;
}

REGISTRY_WSJCPP_EMPLOY(EmployCycle1)

// ---------------------------------------------------------------------

EmployCycle2::EmployCycle2() : WsjcppEmployBase({EmployCycle2::name()}, {"unit-test-employ1", EmployCycle1::name() }) {
  TAG = EmployCycle2::name();
}

bool EmployCycle2::init(const std::string &sName, bool bSilent) {
  m_sValue = "";
  return true;
}

bool EmployCycle2::deinit(const std::string &sName, bool bSilent) {
  m_sValue = "";
  return true;
}

REGISTRY_WSJCPP_EMPLOY(EmployCycle2)

// ---------------------------------------------------------------------

EmployCycle3::EmployCycle3() : WsjcppEmployBase({IEmployCycle3::name()}, {"unit-test-employ1", EmployCycle2::name() }) {
  TAG = IEmployCycle3::name();
}

bool EmployCycle3::init(const std::string &sName, bool bSilent) {
  m_sValue = "";
  return true;
}
bool EmployCycle3::deinit(const std::string &sName, bool bSilent) {
  m_sValue = "";
  return true;
}

// REGISTRY_WSJCPP_EMPLOY(EmployCycle3)

// ---------------------------------------------------------------------

int main() {
  std::string msg_error = "";
  try {
    REGISTRY_WSJCPP_EMPLOY(EmployCycle3)
  } catch(const std::exception &e) {
    msg_error = std::string(e.what());
    if (msg_error != "Cycle dependency: IEmployCycle3 -> EmployCycle2 -> EmployCycle1 -> IEmployCycle3") {
      return -1;
    }
  }
  return 0;
}
