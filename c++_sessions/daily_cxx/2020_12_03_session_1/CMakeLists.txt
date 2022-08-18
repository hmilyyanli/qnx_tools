cmake_minimum_required(VERSION 3.18)

project(session1 CXX)

include(CTest)

add_executable(session1 session1.m.cpp)

add_test(NAME session1 COMMAND session1)
