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

project(pmi CXX)

include(CTest)

add_library(
    ${PROJECT_NAME}-core
        ${PROJECT_NAME}_core.h
        ${PROJECT_NAME}_core.cpp
)

target_include_directories(
    ${PROJECT_NAME}-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
