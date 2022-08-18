cmake_minimum_required(VERSION 3.17)

project(expected CXX)

include(CTest)

set(vfc_ROOT C:/Users/poh2lr/.nuget/packages/vfc/0.0.0)

find_package(vfc 0.0.0 REQUIRED COMPONENTS core)

set(HelperDir d:/repos/c2wd_libs/vaddons/core/src)
set(HelperDir2 d:/cxx/fvg3_lfs_1/c_if/c2wd_libs_binaries/vaddons/inc/)

file(GLOB asco
    d:/repos/c2wd_libs/vaddons/core/src/assertion_handling/*
)

add_executable(
    ${PROJECT_NAME}
        ${PROJECT_NAME}.m.cpp
        ${HelperDir}/error_handling/vad_errh_system_error.cpp
        ${HelperDir}/error_handling/vad_errh_system_error.cpp
        ${HelperDir}/vaddons.natvis
        ${asco}
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        vfc::vfc-core
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${HelperDir}/inc
        ${HelperDir2}
)

add_test(
    NAME
        ${PROJECT_NAME}
    COMMAND
        ${PROJECT_NAME}
)
