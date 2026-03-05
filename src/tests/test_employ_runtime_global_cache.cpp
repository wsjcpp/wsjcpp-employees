#include <vector>
#include <iostream>
#include <wsjcpp_employees.h>


int main() {
    std::cout << "test cache" << std::endl;
    WsjcppEmployeesInit employees({}, false);
    if (!employees.initialized) {
        return -1;
    }
    WsjcppEmployRuntimeGlobalCache *pCache = findWsjcppEmploy<WsjcppEmployRuntimeGlobalCache>();
    pCache->set("name1", "value3y2hf9f3h%%");
    if (!pCache->has("name1")) {
        return -1;
    }
    if (pCache->has("name2")) {
        return -1;
    }
    if (pCache->get("name1") != "value3y2hf9f3h%%") {
        return -1;
    }
    return 0;
}
