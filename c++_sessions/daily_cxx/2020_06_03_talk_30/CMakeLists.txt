cmake_minimum_required(VERSION 3.17)

project(error_code_client CXX)

include(CTest)

add_executable(
    ${PROJECT_NAME}
        ${PROJECT_NAME}.m.cpp
)

add_test(
    NAME
        ${PROJECT_NAME}
    COMMAND
        ${PROJECT_NAME}
)
