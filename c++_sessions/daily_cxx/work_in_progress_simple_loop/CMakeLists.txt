cmake_minimum_required(VERSION 3.15)

project(simple_loop CXX)

foreach(name RANGE 1 4)
    set(libname ${PROJECT_NAME}${name})
    add_executable(${libname} ${libname}.cpp)
endforeach()

# add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
# 
# enable_testing()
# add_test(NAME ${PROJECT_NAME}.cpp COMMAND ${PROJECT_NAME})
