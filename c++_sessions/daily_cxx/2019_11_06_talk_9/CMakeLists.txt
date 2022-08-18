cmake_minimum_required(VERSION 3.12...3.15)

project(state_pattern
    DESCRIPTION "Example for the state pattern"
    LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.m.cpp
    public_state_module.h public_state_module.cpp
    private_state_module.h)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
