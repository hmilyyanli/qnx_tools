cmake_minimum_required(VERSION 3.15)

project(simple_fiasco
    LANGUAGES CXX
    DESCRIPTION
    "Provide simple examples for the static initialization order fisco")

add_executable(
    ${PROJECT_NAME}
    main.cpp # main

    fiasco.cpp  # solution using nifty counter
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#enable_testing()
#add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
