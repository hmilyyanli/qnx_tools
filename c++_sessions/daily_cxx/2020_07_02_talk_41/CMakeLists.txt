cmake_minimum_required(VERSION 3.17)

project(raii CXX)

include(CTest)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_NAME}.m.cpp
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
