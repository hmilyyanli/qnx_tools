cmake_minimum_required(VERSION 3.12...3.15)

project(move_and_embedded_part_2
    DESCRIPTION "Complementary C++ Code to the talk"
    HOMEPAGE_URL "https://sourcecode.socialcoding.bosch.com/users/poh2lr/repos/reveal.js/browse?at=refs%2Fheads%2F2019-10-18_daily_cxx_6"
    LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.m.cpp)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
