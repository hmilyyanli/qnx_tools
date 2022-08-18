cmake_minimum_required(VERSION 3.15)

project(
    cpp_core_guidelines_c_67
    DESCRIPTION "Teaching Cpp Core Guideline Rule C.67"
    HOMEPAGE_URL "https://sourcecode.socialcoding.bosch.com/users/poh2lr/repos/daily_cxx/browse"
    LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.m.cpp)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
