cmake_minimum_required(VERSION 3.0.0)
project(cpp_study VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("${PROJECT_SOURCE_DIR}"/program)
include_directories("${PROJECT_SOURCE_DIR}"/leetcode)

add_executable(solution program/solution.cpp)
add_executable(cpp_study main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
