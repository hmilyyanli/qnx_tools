cmake_minimum_required(VERSION 3.17)

project(slicing CXX)

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
