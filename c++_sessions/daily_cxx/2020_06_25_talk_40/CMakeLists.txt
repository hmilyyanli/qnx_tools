cmake_minimum_required(VERSION 3.17)

project(env_trick CXX)

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
