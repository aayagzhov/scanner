cmake_minimum_required(VERSION 3.11)

project(StatLib CXX)
set(CMAKE_CXX_STANDARD 17)

set(MAIN_FILES printer.h printer.cpp)

add_library(StatLib STATIC ${MAIN_FILES})