#=============================================================================
#  C O P Y R I G H T
#-----------------------------------------------------------------------------
#  Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
#
#  This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
#  distribution is an offensive act against international law and may be
#  prosecuted under federal law. Its content is company confidential.
#=============================================================================
# Maintainer: C2W-Drive (CC-DA/ESV1)

cmake_minimum_required(VERSION 3.17)

project(vont CXX)

include(CTest)

add_library(
    ${PROJECT_NAME}
        ${PROJECT_NAME}_registrator.hpp
        ${PROJECT_NAME}_registrator.cpp
        ${PROJECT_NAME}_mofu.cpp
        ${PROJECT_NAME}_sepa.cpp
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
    ${PROJECT_NAME}_client
        ${PROJECT_NAME}_client.m.cpp
)
target_link_libraries(
    ${PROJECT_NAME}_client
    PRIVATE
        ${PROJECT_NAME}
)

add_test(
    NAME
        ${PROJECT_NAME}_client
    COMMAND
        ${PROJECT_NAME}_client
)
set_tests_properties(
    ${PROJECT_NAME}_client
    PROPERTIES
        PASS_REGULAR_EXPRESSION
            "size: 2"
)
