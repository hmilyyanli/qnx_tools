cmake_minimum_required(VERSION 3.17)

project(
    decorator
    DESCRIPTION "Code example for the decorator pattern"
    LANGUAGES CXX
)

include(CTest)

# =============================================================================
#                                    TARGETS
# -----------------------------------------------------------------------------

set(Modules
    dec_output_stream_protocol
    dec_cost_function_protocol
)

foreach(m ${Modules})
    list(APPEND SrcFiles
        ${m}.hpp
        ${m}.cpp
    )
    list(APPEND TestFiles
        ${m}.t.cpp
    )
endforeach()

add_library(
    ${PROJECT_NAME}
    ${SrcFiles}
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# =============================================================================
#                                     TESTS
# -----------------------------------------------------------------------------

foreach(t ${TestFiles})
    add_executable(
        ${t}
        ${t}
    )
    target_link_libraries(
        ${t}
        PRIVATE
            ${PROJECT_NAME}
    )
    
    add_test(
        NAME
            ${t}
        COMMAND
            ${t}
    )
endforeach()
