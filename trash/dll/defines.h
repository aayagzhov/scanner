#pragma once

#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
    #ifdef LIB_DLL
        #ifdef __GNUC__
            #define LIB_DLL_EXPORT_DECL __attribute__ ((dllexport))
        #else
            #define LIB_DLL_EXPORT_DECL __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define LIB_DLL_EXPORT_DECL __attribute__ ((dllimport))
        #else
            #define LIB_DLL_EXPORT_DECL __declspec(dllimport)
        #endif
    #endif
#else
    #define LIB_DLL_EXPORT_DECL __attribute__ ((visibility ("default")))
#endif

#define LIB_DLL_EXPORT extern "C" LIB_DLL_EXPORT_DECL