cmake_minimum_required(VERSION 3.15)

project(iterator_pattern
    DESCRIPTION "Code example for the iterator pattern"
    LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.m.cpp)

enable_testing()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
