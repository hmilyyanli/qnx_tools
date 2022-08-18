cmake_minimum_required(VERSION 3.18)

project(session2 CXX)

include(CTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(session2 lifecycle.m.cpp)

add_test(NAME session2 COMMAND session2)
