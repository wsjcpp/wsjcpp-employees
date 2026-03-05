# wsjcpp-employees Changelog

All notable changes to wsjcpp-yaml project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [v0.2.1] - 2026-03-05 (2026 March 5)

- fix: renamed 'recoursiveTestDependencies' to 'recursiveTestDependencies'
- fix-names: renamed 'inited' to 'initialized'
- Added define REGISTRY_WSJCPP_EMPLOY
- fix namings: renamed REGISTRY_WJSCPP_SERVICE_LOCATOR to REGISTRY_WSJCPP_SERVICE_LOCATOR
- Fix build tests
- Removed define WSJCPP_EMPLOYEES_VERSION_0_2_0
- Added define WSJCPP_EMPLOYEES_VERSION_0_2_1
- Removed define REGISTRY_WSJCPP_SERVICE_LOCATOR
- Moved all tests for ctest (before exclude dependency wsjcpp_core)

## [v0.2.0] - 2025-06-29 (2025 July 29)

- Updated wsjcpp-core to v0.2.3 (Up C++ from 11 to 17)
- Change single name registration to multiple names
- Added silent mode
- Added class for simplify init `WsjcppEmployeesInit`
- Added copyrights to files
- Added new defines with version WSJCPP_EMPLOYEES_VERSION_* for using in target project differences
- Added .clang-format
