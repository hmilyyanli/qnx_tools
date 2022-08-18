cmake_minimum_required(VERSION 3.17)

project(no_default_in_switch_case)

include(CTest)

add_library(lib
    lib1.cpp
    lib2.cpp)

add_executable(exe1 main.cpp)
target_link_libraries(exe1 PRIVATE lib)

add_test(
    NAME
        exe1
    COMMAND
        exe1
)

add_executable(exe2
    lib1.cpp
    lib2.cpp
    main.cpp
)

add_test(
    NAME
        exe2
    COMMAND
        exe2
)


add_library(dynlib SHARED
    lib1.cpp
    lib2.cpp)

add_executable(exe3 main.cpp)
target_link_libraries(exe3 PRIVATE dynlib)

add_test(
    NAME
        exe3
    COMMAND
        exe3
)
