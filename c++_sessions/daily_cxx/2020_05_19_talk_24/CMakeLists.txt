cmake_minimum_required(VERSION 3.17)

project(never_mix_signed_and_unsigned CXX)

include(CTest)

add_executable(
    ${PROJECT_NAME}.t
        ${PROJECT_NAME}.t.cpp
)

enable_testing()
add_test(
    NAME
        ${PROJECT_NAME}.t
    COMMAND
        ${PROJECT_NAME}.t
)
set_tests_properties(
    ${PROJECT_NAME}.t
    PROPERTIES
        PASS_REGULAR_EXPRESSION
            "hello .*world!"
)
