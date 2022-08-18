cmake_minimum_required(VERSION 3.17)

string(MD5 HashValue "${CIN}")
set(FileName ${HashValue}.txt)
file(WRITE ${FileName} "${CIN}")

execute_process(
    COMMAND ${EXE}
    INPUT_FILE ${FileName}
    RESULT_VARIABLE ErrorCode
    COMMAND_ECHO STDOUT
)

if(NOT ErrorCode EQUAL 0)
    message(FATAL_ERROR "ErrorCode(${ErrorCode})")
endif()
