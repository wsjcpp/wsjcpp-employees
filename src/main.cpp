#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    if (!WSJCppCore::dirExists(".logs")) {
        WSJCppCore::makeDir(".logs");
    }
    WSJCppLog::setPrefixLogFile("wsjcpp-employees");
    WSJCppLog::setLogDirectory(".logs");
    
    if (!WSJCppEmployees::init({})) {
        WSJCppLog::err(TAG, "Could not init employees");
        return -1;
    }

    // TODO your code here
    return 0;
}
