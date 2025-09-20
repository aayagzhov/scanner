cmake_minimum_required(VERSION 3.11)

project(Scanner VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")

enable_testing()

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)