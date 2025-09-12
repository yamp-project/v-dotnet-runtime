#ifndef YAMP_SDK_COMMON_H
#define YAMP_SDK_COMMON_H

#ifdef __cplusplus
#define EXTERN extern "C"
#define BEGIN_SDK EXTERN {
#define END_SDK }
#else
#include <stdbool.h>
#define EXTERN
#define BEGIN_SDK
#define END_SDK
#endif

#ifdef YAMP_EXPORT_FUNCTION
    #ifdef _WIN32
        #define YAMP_EXPORT EXTERN __declspec(dllexport)
    #elif defined(__linux__)
        #define YAMP_EXPORT EXTERN __attribute__((visibility("default")))
    #endif
#else
    #ifdef _WIN32
        #define YAMP_EXPORT EXTERN __declspec(dllimport)
    #elif defined(__linux__)
        #define YAMP_EXPORT EXTERN
    #endif
#endif

#ifndef SDK_EXPORT
    #ifdef _WIN32
        #define SDK_EXPORT EXTERN __declspec(dllexport)
    #elif defined(__linux__)
        #define SDK_EXPORT EXTERN __attribute__((visibility("default")))
    #endif
#endif

#endif // YAMP_SDK_COMMON_H
