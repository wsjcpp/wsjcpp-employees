#!/bin/bash

clang-format -style=file -i src/main.cpp
clang-format -style=file -i src/my_impl.h
clang-format -style=file -i src/employ_my_impl.cpp
clang-format -style=file -i src/employ_my_impl.h
clang-format -style=file -i src/wsjcpp_employees.h
clang-format -style=file -i src/wsjcpp_employees.cpp
