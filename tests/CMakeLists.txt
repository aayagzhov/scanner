include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)

add_executable(tests ${SRC_FILES})

target_include_directories(tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/include
        ${gtest_SOURCE_DIR}/include
        ${gtest_BINARY_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(tests)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

target_link_libraries(tests PRIVATE ScannerLib gtest_main ${SYSTEM_LIBS})