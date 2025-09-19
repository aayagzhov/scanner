cmake_minimum_required(VERSION 3.11)

project(DllLib CXX)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "^MINGW")
    set(SYSTEM_LIBS -lstdc++)
else()
    set(SYSTEM_LIBS)
endif()

# создаём динамическую библиотеку из трёх файлов
# цель назовём ImgLibDll
add_library(DllLib SHARED
            interface.h
            interface.cpp
            defines.h)

# При компоновке динамической библиотеки будем использовать статическую.
# Для этого добавим к ней цель ImgLib
target_link_libraries(DllLib ${SYSTEM_LIBS})

# определяем для сборки ImgLibDll макрос IMGLIB_DLL,
# чтобы экспорт функций получился правильным
target_compile_definitions(DllLib PRIVATE LIB_DLL)