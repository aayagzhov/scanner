file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
)

add_library(ScannerLib SHARED ${SRC_FILES})

target_include_directories(ScannerLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/include>
    $<INSTALL_INTERFACE:include>
)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

target_link_libraries(ScannerLib ${SYSTEM_LIBS})

target_compile_definitions(ScannerLib PRIVATE LIB_DLL)
