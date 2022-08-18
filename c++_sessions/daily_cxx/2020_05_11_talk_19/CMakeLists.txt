cmake_minimum_required(VERSION 3.17)

project(vad_compile_time_predicates CXX)

include(CTest)

add_executable(
    ${PROJECT_NAME}.t
    ${PROJECT_NAME}.t.cpp
)
target_include_directories(${PROJECT_NAME}.t
    PUBLIC
        $ENV{HOME}/prefix/vaddons/inc
)

add_test(
    NAME
        ${PROJECT_NAME}.t
    COMMAND
        ${PROJECT_NAME}.t
)
