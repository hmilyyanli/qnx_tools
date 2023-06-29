cmake_minimum_required(VERSION 3.14...3.15)

project(fibonacci CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)

enable_testing()

add_test(NAME ${PROJECT_NAME}.cpp COMMAND ${PROJECT_NAME})
