add_executable(app
    main.cpp)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

target_link_libraries(app PRIVATE ScannerLib ${SYSTEM_LIBS})