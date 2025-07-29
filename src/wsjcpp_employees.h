#ifndef WSJCPP_EMPLOYEES_H
#define WSJCPP_EMPLOYEES_H

#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <wsjcpp_core.h>

#define WSJCPP_EMPLOYEES_VERSION_0_2_0
#define WSJCPP_EMPLOYEES_VERSION_0_2
#define WSJCPP_EMPLOYEES_VERSION_0

// ---------------------------------------------------------------------
// base employ class

class WsjcppEmployBase {
public:
  WsjcppEmployBase(const std::vector<std::string> &vNames, const std::vector<std::string> &vLoadAfter);
  virtual ~WsjcppEmployBase();
  virtual bool init(const std::string &sName, bool bSilent) = 0;
  virtual bool deinit(const std::string &sName, bool bSilent) = 0;
  const std::vector<std::string> &loadAfter();

private:
  std::string TAG;
  std::vector<std::string> m_vNames;
  std::vector<std::string> m_vLoadAfter;
};

// ---------------------------------------------------------------------
// public employees

extern std::map<std::string, WsjcppEmployBase *> *g_pWsjcppEmployees;
extern std::vector<std::string> *g_pWsjcppInitEmployees;

class WsjcppEmployees {
public:
  static void initGlobalVariables();
  static void deinitGlobalVariables();
  static void addEmploy(const std::string &sName, WsjcppEmployBase *pEmploy);
  static bool init(const std::vector<std::string> &vLoadAfter, bool bSilent = false);
  static bool deinit(bool bSilent = false);
  static void recoursiveTestDependencies(const std::vector<std::string> &v);
};

// ---------------------------------------------------------------------
// WsjcppEmployeesInit

struct WsjcppEmployeesInit {
  const bool inited;
  bool deinited;
  bool silent;
  WsjcppEmployeesInit(const std::vector<std::string> &vLoadAfter, bool bSilent = false)
    : silent(bSilent), deinited(false), inited(WsjcppEmployees::init(vLoadAfter, bSilent)) {}
  ~WsjcppEmployeesInit() { this->deinit(); }
  bool deinit() {
    if (inited && !deinited) {
      deinited = WsjcppEmployees::deinit(silent);
    }
    return deinited;
  }
};

// ---------------------------------------------------------------------
// RegistryServiceLocator
#define REGISTRY_WJSCPP_SERVICE_LOCATOR(classname)                                                                     \
  static classname *pWJSCppRegistryServiceLocator##classname = new classname();

// ---------------------------------------------------------------------
// findWsjcppEmploy

template <class T> T *findWsjcppEmploy() {
  WsjcppEmployees::initGlobalVariables();
  std::string TAG = "findWsjcppEmploy";
  std::string sEmployName = T::name();
  WsjcppEmployBase *pEmploy = NULL;
  if (g_pWsjcppEmployees->count(sEmployName)) {
    pEmploy = g_pWsjcppEmployees->at(sEmployName);
  }
  if (pEmploy == NULL) {
    WsjcppLog::throw_err(TAG, "Not found employ " + sEmployName);
  }
  T *pTEmploy = dynamic_cast<T *>(pEmploy);
  if (pTEmploy == NULL) {
    WsjcppLog::throw_err(TAG, "Employ could not cast to T [" + sEmployName + "]");
  }
  return pTEmploy;
}

// ---------------------------------------------------------------------
// WsjcppEmployRuntimeGlobalCache

class WsjcppEmployRuntimeGlobalCache : public WsjcppEmployBase {
public:
  WsjcppEmployRuntimeGlobalCache();
  static std::string name() { return "WsjcppEmployRuntimeGlobalCache"; }
  virtual bool init(const std::string &sName, bool bSilent) override;
  virtual bool deinit(const std::string &sName, bool bSilent) override;
  void set(const std::string &sName, const std::string &sValue);
  bool has(const std::string &sName);
  std::string get(const std::string &sName);

private:
  std::string TAG;
  std::map<std::string, std::string> m_sStringMap;
};

#endif // WSJCPP_EMPLOYEES_H
