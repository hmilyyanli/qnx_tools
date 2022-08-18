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

project(sfinae CXX)

include(CTest)

add_executable(
    ${PROJECT_NAME}.t
        ${PROJECT_NAME}.t.cpp
)
target_include_directories(
    ${PROJECT_NAME}.t
    PRIVATE
        $ENV{HOME}/prefix/vaddons/inc
)

add_test(
    NAME
        ${PROJECT_NAME}.t
    COMMAND
        ${PROJECT_NAME}.t
)
