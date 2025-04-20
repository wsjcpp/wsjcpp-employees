cmake_minimum_required(VERSION 3.5)

project(wsjcpp-employees C CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

#### BEGIN_WSJCPP_APPEND
list (APPEND WSJCPP_SOURCES "./src/employ_my_impl.cpp")
#### END_WSJCPP_APPEND

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp-employees_SOURCE_DIR})

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "src/main.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_employees.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_employees.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp-employees ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp-employees ${WSJCPP_LIBRARIES})

install(
    TARGETS
        wsjcpp-employees
    RUNTIME DESTINATION
        /usr/bin
)


