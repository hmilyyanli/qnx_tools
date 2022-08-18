cmake_minimum_required (VERSION 3.8)

project(store_project)

### Add library which we want to test###
include_directories(src)
add_library(store_lib STATIC "src/store.cpp" "src/store.h")

### Add Gooogletest ###

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(third_party/googletest-release-1.8.1)
# add_subdirectory(third_party/googletest-release-1.10.0)
# Tests need to be enabled once in CMake
enable_testing()

### Add tests ###
add_executable(store_test test/store_test.cpp)
target_link_libraries(store_test PUBLIC store_lib gtest_main)
add_test(NAME store_test COMMAND store_test)

