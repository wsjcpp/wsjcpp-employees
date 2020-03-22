#include "wsjcpp_employees.h"
#include <algorithm>
#include <wsjcpp_core.h>
#include <iostream>

// ---------------------------------------------------------------------

std::map<std::string, WSJCppEmployBase*> *g_pWSJCppEmployees = nullptr;
std::vector<std::string> *g_pWSJCppInitEmployees = nullptr;

// ---------------------------------------------------------------------

void WSJCppEmployees::initGlobalVariables() {
    if (g_pWSJCppEmployees == nullptr) {
        // WSJCppLog::info(std::string(), "Create employees map");
        g_pWSJCppEmployees = new std::map<std::string, WSJCppEmployBase*>();
    }
    if (g_pWSJCppInitEmployees == nullptr) {
        // WSJCppLog::info(std::string(), "Create init employees vector");
        g_pWSJCppInitEmployees = new std::vector<std::string>();
    }
}

// ---------------------------------------------------------------------

void WSJCppEmployees::deinitGlobalVariables() {
    if (g_pWSJCppEmployees != nullptr) {
        std::map<std::string, WSJCppEmployBase*>::iterator it;
        for (it = g_pWSJCppEmployees->begin(); it != g_pWSJCppEmployees->end(); ++it) {
            std::string sName = it->first;
            delete it->second;
            it->second = nullptr;
        }
        g_pWSJCppEmployees->clear();
        delete g_pWSJCppEmployees;
        g_pWSJCppEmployees = nullptr;
    }

    if (g_pWSJCppInitEmployees != nullptr) {
        g_pWSJCppInitEmployees->clear();
        delete g_pWSJCppInitEmployees;
        g_pWSJCppInitEmployees = nullptr;
    }
}

// ---------------------------------------------------------------------

void WSJCppEmployees::addEmploy(const std::string &sName, WSJCppEmployBase* pEmploy) {
    WSJCppEmployees::initGlobalVariables();
    if (g_pWSJCppEmployees->find(sName) != g_pWSJCppEmployees->end()) {
        WSJCppLog::err(sName, "Already registered");
    } else {
        g_pWSJCppEmployees->insert(std::pair<std::string, WSJCppEmployBase*>(sName,pEmploy));
        // WSJCppLog::info(sName, "Registered");
    }
}

// ---------------------------------------------------------------------

bool WSJCppEmployees::init(const std::vector<std::string> &vStart) {
    WSJCppEmployees::initGlobalVariables();

    for (unsigned int i = 0; i < vStart.size(); i++) {
        g_pWSJCppInitEmployees->push_back(vStart[i]);
    }

    std::string TAG = "Employees_init";
    bool bRepeat = true;
    while (bRepeat) {
        bRepeat = false;
        std::map<std::string, WSJCppEmployBase*>::iterator it = g_pWSJCppEmployees->begin();
        for (; it!=g_pWSJCppEmployees->end(); ++it) {
            std::string sEmployName = it->first;
            WSJCppEmployBase *pEmploy = it->second;

            if (std::find(g_pWSJCppInitEmployees->begin(), g_pWSJCppInitEmployees->end(), sEmployName) != g_pWSJCppInitEmployees->end()) {
                continue;
            }

            unsigned int nRequireLoaded = 0;
            for (unsigned int i = 0; i < pEmploy->loadAfter().size(); i++) {
                std::string sRequireEmploy = pEmploy->loadAfter()[i];
                if (std::find(g_pWSJCppInitEmployees->begin(), g_pWSJCppInitEmployees->end(), sRequireEmploy) != g_pWSJCppInitEmployees->end()) {
                    nRequireLoaded++;
                }
            }
            if (pEmploy->loadAfter().size() == nRequireLoaded) {
                if (!pEmploy->init()) {
                    WSJCppLog::err(TAG, "Init " + sEmployName + " ... FAIL");
                    return false;
                }
                g_pWSJCppInitEmployees->push_back(sEmployName);
                bRepeat = true;
                WSJCppLog::ok(TAG, "Init " + sEmployName + " ... OK");
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------

// WSJCppEmployBase
WSJCppEmployBase::WSJCppEmployBase(const std::string &sName, const std::vector<std::string> &vAfter) {
    TAG = sName;
    m_sName = sName;

    for (unsigned int i = 0; i < vAfter.size(); i++) {
        m_vLoadAfter.push_back(vAfter[i]);
    }
    WSJCppEmployees::addEmploy(m_sName, this);
}

// ---------------------------------------------------------------------

WSJCppEmployBase::~WSJCppEmployBase() {
    // nothing
}

// ---------------------------------------------------------------------

bool WSJCppEmployBase::init() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void WSJCppEmployBase::deinit() {
    // nothing
}

// ---------------------------------------------------------------------

const std::vector<std::string> &WSJCppEmployBase::loadAfter() {
    return m_vLoadAfter;
}


// ---------------------------------------------------------------------
// WJSCppEmployRuntimeGlobalCache

REGISTRY_WJSCPP_EMPLOY(WJSCppEmployRuntimeGlobalCache)

// ---------------------------------------------------------------------

WJSCppEmployRuntimeGlobalCache::WJSCppEmployRuntimeGlobalCache()
    : WSJCppEmployBase(WJSCppEmployRuntimeGlobalCache::name(), {}) {

    TAG = WJSCppEmployRuntimeGlobalCache::name();
}

// ---------------------------------------------------------------------

bool WJSCppEmployRuntimeGlobalCache::init() {
    // checking settings
    WSJCppLog::info(TAG, "init");
    return true;
}

// ---------------------------------------------------------------------

void WJSCppEmployRuntimeGlobalCache::set(const std::string &sName, const std::string &sValue) {
    m_sStringMap[sName] = sValue;
}

// ---------------------------------------------------------------------

bool WJSCppEmployRuntimeGlobalCache::has(const std::string &sName) {
    return m_sStringMap.find(sName) != m_sStringMap.end();
}

// ---------------------------------------------------------------------

std::string WJSCppEmployRuntimeGlobalCache::get(const std::string &sName) {
    if (m_sStringMap.find(sName) != m_sStringMap.end()) {
        return m_sStringMap[sName];
    }
    return "";
}

// ---------------------------------------------------------------------