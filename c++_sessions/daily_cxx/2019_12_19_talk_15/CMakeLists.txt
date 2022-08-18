cmake_minimum_required(VERSION 3.15)

project(static_initialization_order_fiasco
    LANGUAGES CXX
    DESCRIPTION
    "Provide some examples for the static initialization order fisco")

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_NAME}.m.cpp # main

    dxx_raii_object.cpp   # provides a logger type
    dxx_siu_metre.cpp     # provides a constexpr type

    dxx_siof_globals.cpp  # static initialization order fiasco

    dxx_con_globals.cpp   # solution using constexpr
    dxx_iofu_globals.cpp  # solution using init on first use
    dxx_ncnt_globals.cpp  # solution using nifty counter
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
