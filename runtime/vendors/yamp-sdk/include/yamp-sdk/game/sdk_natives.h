#ifndef YAMP_SDK_GAME_NATIVES_H
#define YAMP_SDK_GAME_NATIVES_H

#include "yamp-sdk/sdk_common.h"

#include <cstdint>

BEGIN_SDK

typedef enum CNativeValueType
{
    UNKNOWN_TYPE = 0,
    VOID_TYPE = 1,
    BOOL_TYPE = 2,
    INT_TYPE = 3,
    UINT_TYPE = 4,
    FLOAT_TYPE = 5,
    STRING_TYPE = 6,
    VECTOR_TYPE = 7,
    ANY_TYPE = 8,
} CNativeValueType;

typedef struct CNativeValueInformation
{
    CNativeValueType m_Type;
    bool m_IsPointer;
} CNativeValueInformation;

typedef struct CNativeInformation
{
    uint64_t m_Hash;
    char* m_Name;
    CNativeValueInformation* m_ParameterValueArrayData;
    int m_ParameterValueArraySize;
    CNativeValueInformation m_ReturnValue;
} CNativeInformation;

typedef struct CNativeInvoker CNativeInvoker;
typedef struct CNativeReflection CNativeReflection;

typedef struct SDK_NativesFactory
{
    CNativeInvoker* (*CreateInvoker)();

    void (*Begin)(CNativeInvoker* nativeInvoker, uint64_t nativeHash);
    void (*Reset)(CNativeInvoker* nativeInvoker);
    void (*Call)(CNativeInvoker* nativeInvoker);

    void (*PushBuffer)(CNativeInvoker* nativeInvoker, void* value);
    void (*PushBool)(CNativeInvoker* nativeInvoker, bool value);
    void (*PushInteger)(CNativeInvoker* nativeInvoker, int32_t value);
    void (*PushUnsignedInteger)(CNativeInvoker* nativeInvoker, uint32_t value);
    void (*PushFloat)(CNativeInvoker* nativeInvoker, float value);
    void (*PushString)(CNativeInvoker* nativeInvoker, const char* value);
    void (*PushArgumentFromBuffer)(CNativeInvoker* nativeInvoker, void* argumentBuffer, uint8_t argumentSize);

    void* (*GetReturnValueBuffer)(CNativeInvoker* nativeInvoker);
    bool (*IsNativePresent)(CNativeInvoker* nativeInvoker, uint64_t nativeHash);

    CNativeReflection* (*CreateReflection)();
    CNativeInformation* (*GetNativeInformation)(CNativeReflection* nativeReflection, uint64_t nativeHash);
    bool (*GetListOfNatives)(CNativeReflection* nativeReflection, uint64_t** array, int* arraySize);
} SDK_NativesFactory;

END_SDK

#endif // YAMP_SDK_GAME_NATIVES_H
