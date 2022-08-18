cmake_minimum_required(VERSION 3.17)

project(flag_enum CXX)

include(CTest)

add_executable(
    ${PROJECT_NAME}
        ${PROJECT_NAME}.t.cpp
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        d:/repos/c2wd_libs/vaddons/core/inc
)


enable_testing()
add_test(
    NAME
        ${PROJECT_NAME}.t
    COMMAND
        ${PROJECT_NAME}.t
)
