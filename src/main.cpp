#include <wsjcpp_core.h>
#include <wsjcpp_employees.h>

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_APP_NAME);
    std::string appVersion = std::string(WSJCPP_APP_VERSION);
    if (!WsjcppCore::dirExists(".logs")) {
        WsjcppCore::makeDir(".logs");
    }
    WsjcppLog::setPrefixLogFile("wsjcpp-employees");
    WsjcppLog::setLogDirectory(".logs");
    
    if (!WsjcppEmployees::init({})) {
        WsjcppLog::err(TAG, "Could not init employees");
        return -1;
    }

    // TODO your code here
    return 0;
}
