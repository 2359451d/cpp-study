project(main)
include_directories("${PROJECT_SOURCE_DIR}"/program)
add_executable(hello program/hello.cpp)