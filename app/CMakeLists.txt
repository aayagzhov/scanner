add_executable(app main.cpp)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(app PRIVATE ScannerLib)

#add_custom_command(TARGET app POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:ScannerLib>
#        $<TARGET_FILE_DIR:app>
#)