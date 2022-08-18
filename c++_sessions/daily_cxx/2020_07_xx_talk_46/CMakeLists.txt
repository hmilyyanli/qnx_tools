cmake_minimum_required(VERSION 3.17)

project(writing_a_program CXX)

include(CTest)

add_executable(
    calculator
    calculator.m.cpp
)

add_executable(
    calculator2
    calculator2.m.cpp
)

function(TestSingleExpression Name Exe Expression Result)
    set(ScriptPath ${CMAKE_CURRENT_SOURCE_DIR}/WrapCin.script.cmake)
    add_test(
        NAME ${Name}
        COMMAND ${CMAKE_COMMAND} -D CIN=${Expression}
                -D EXE=${CMAKE_CURRENT_BINARY_DIR}/${Exe} -P ${ScriptPath}
    )
    set_tests_properties(${Name} PROPERTIES
        PASS_REGULAR_EXPRESSION "${Result}"
    )
endfunction()

TestSingleExpression(Plus calculator 3+4 7)
TestSingleExpression(Minus calculator 3-5 -2)

TestSingleExpression(Plus2 calculator2 3+4x 7)
TestSingleExpression(Minus2 calculator2 3-5x -2)
TestSingleExpression(GaussSum calculator2 1+2+3+4x 10)
TestSingleExpression(StdUseCase calculator2 3*4+2x 14)
TestSingleExpression(StdUseCaseSym calculator2 2+3*4x 14)
# TestSingleExpression(StdUseCase calculator2 2+3.1*4x 14.4)
