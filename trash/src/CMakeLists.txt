# cmake_minimum_required(VERSION 3.11)

# project(HelloCMake CXX)
# set(CMAKE_CXX_STANDARD 17)

# if(CMAKE_SYSTEM_NAME MATCHES "^MINGW")
#     set(SYSTEM_LIBS -lstdc++)
# else()
#     set(SYSTEM_LIBS)
# endif()

# add_executable("hello" "src/main.cpp")

# target_link_libraries(hello ${SYSTEM_LIBS})


# cmake_minimum_required(VERSION 3.11)

# project(Hello CXX)
# set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(../stat_lib StatLibBuild)

# add_executable(hello main.cpp)

# target_link_libraries(hello StatLib)
# target_include_directories(hello PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../stat_lib") 






#3
# cmake_minimum_required(VERSION 3.11)

# project(Hello CXX)
# set(CMAKE_CXX_STANDARD 17)

# set(STAT_LIB_DIR CACHE STRING "StatLib static library directory")

# if(NOT STAT_LIB_DIR)
#     message(FATAL_ERROR "Please, specify STAT_LIB_DIR directory via -DSTAT_LIB_DIR=<dir>")
# endif()

# message(STATUS "StatLib dir is ${STAT_LIB_DIR}, change via -DSTAT_LIB_DIR=<dir>")

# add_executable(hello main.cpp)
# target_include_directories(hello PUBLIC "${STAT_LIB_DIR}")
# target_link_directories(hello PUBLIC
#     "${STAT_LIB_DIR}/build"
#     )
# #$<IF:$<CONFIG:Debug>,Debug,Release>
# target_link_libraries(hello StatLib)








#4
# cmake_minimum_required(VERSION 3.11)

# project(LumaCorr CXX)
# set(CMAKE_CXX_STANDARD 17)

# set(IMGLIB_DLL_DIR CACHE STRING "ImgLibDll shared library directory")

# if(NOT IMGLIB_DLL_DIR)
#     message(FATAL_ERROR "Please, specify ImgLibDll directory via -DIMGLIB_DLL_DIR=<dir>")
# endif()
# message(STATUS "ImgLibDll dir is ${IMGLIB_DLL_DIR}, change via -DIMGLIB_DLL_DIR=<dir>")

# if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
#     set(SYSTEM_LIBS -lstdc++)
# else()
#     set(SYSTEM_LIBS)
# endif()

# add_executable(lumacorr main.cpp)

# target_include_directories(lumacorr PUBLIC "${IMGLIB_DLL_DIR}/include")

# # В команде target_link_libraries нужно указать полный путь к файлу библиотеки
# if(EXISTS "${IMGLIB_DLL_DIR}/lib/libImgLibDll.dll.a")
#     target_link_libraries(lumacorr "${IMGLIB_DLL_DIR}/lib/libImgLibDll.dll.a" ${SYSTEM_LIBS})
# else()
#     target_link_libraries(lumacorr "${IMGLIB_DLL_DIR}/lib/libImgLibDll.so" ${SYSTEM_LIBS})
# endif()


# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.