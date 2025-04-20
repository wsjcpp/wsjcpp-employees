#ifndef MY_IMPL_H
#define MY_IMPL_H

#include <string>

class IMyImpl {
    public:
        static std::string name() { return "IMyImpl"; }
        virtual void doSomething() = 0;
};

class IMyImpl2 {
    public:
        static std::string name() { return "IMyImpl2"; }
        virtual void doSomething2() = 0;
};

#endif // MY_IMPL_H
