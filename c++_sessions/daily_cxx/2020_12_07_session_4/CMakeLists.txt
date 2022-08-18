cmake_minimum_required(VERSION 3.19)

project(session4 CXX)

include(CTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(session4 DemoCopyElision.m.cpp)

add_test(NAME session4 COMMAND session4)
