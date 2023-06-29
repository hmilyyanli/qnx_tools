cmake_minimum_required(VERSION 3.17)

project(prefer_uniform_init CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)

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
