#ifndef EMPLOY_MY_IMPL_H
#define EMPLOY_MY_IMPL_H

#include <wsjcpp_employees.h>
#include "my_impl.h"

class EmployMyImpl : public WsjcppEmployBase, public IMyImpl, public IMyImpl2 {
    public:
        EmployMyImpl();
        virtual bool init() override;
        virtual bool deinit() override;

        // IMyImpl
        virtual void doSomething() override;

        // IMyImpl2
        virtual void doSomething2() override;

    private:
        std::string TAG;
};

#endif // EMPLOY_MY_IMPL_H
