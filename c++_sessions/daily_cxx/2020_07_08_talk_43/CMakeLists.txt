cmake_minimum_required(VERSION 3.17)

project(dangling_reference CXX)

include(CTest)

# find_package(vfc REQUIRED COMPONENTS core)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_NAME}.m.cpp
)
# target_link_libraries(
#     ${PROJECT_NAME} PRIVATE vfc::vfc-core
# )

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
