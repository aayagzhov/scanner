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

#target_include_directories(tests
#    PRIVATE
#        ${CMAKE_SOURCE_DIR}/lib/include
#        ${gtest_SOURCE_DIR}/include
#        ${gtest_BINARY_DIR}/include
#)

target_link_libraries(tests PRIVATE ScannerLib gtest_main)

add_custom_command(TARGET tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ScannerLib>
        $<TARGET_FILE_DIR:tests>
)


include(GoogleTest)
gtest_discover_tests(tests)