add_executable(app main.cpp)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(app PRIVATE ScannerLib)
