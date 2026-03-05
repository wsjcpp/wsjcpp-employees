file(GLOB ALL_TESTS
     "test_*.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY tests)

# wsjcpp-employees
list (APPEND TEST_CTF01D_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../wsjcpp_employees.cpp")
list (APPEND TEST_CTF01D_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp")

foreach(_TEST ${ALL_TESTS})
    get_filename_component(TESTNAME ${_TEST} NAME_WE)
    add_executable(${TESTNAME}
        ${_TEST}
        ${TEST_CTF01D_SOURCES}
    )
    target_link_libraries(${TESTNAME} -lpthread ${WSJCPP_LIBRARIES})

    add_test(
      NAME ${TESTNAME}
      COMMAND $<TARGET_FILE:${TESTNAME}>
    )
    message(${CMAKE_CURRENT_BINARY_DIR}/tests)
    set_target_properties (${TESTNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY tests)
endforeach()
