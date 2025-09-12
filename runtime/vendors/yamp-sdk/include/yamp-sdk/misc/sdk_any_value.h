#ifndef YAMP_SDK_ANY_VALUE_H
#define YAMP_SDK_ANY_VALUE_H

#include "yamp-sdk/sdk_common.h"

#include <stdbool.h>
#include <cstdint>

BEGIN_SDK

typedef struct CAnyValue CAnyValue;

typedef enum CType {
    C_ANY = 0,
    
    C_INT_64,
    C_INT_32,
    C_INT_16,
    C_INT_8,
    
    C_UINT_64,
    C_UINT_32,
    C_UINT_16,
    C_UINT_8,
    
    C_DOUBLE,
    C_FLOAT,
    C_BOOL,

    C_NULL,
    C_STRING,

    C_ANY_ARRAY,
    C_ARRAY,
    C_DICT,

    C_VECTOR,
    C_DATE,

    COUNT
} CType;

typedef struct CAnyArray {
    uint8_t size;
    CAnyValue** buffer;
} CAnyArray;

typedef struct CArray {
    uint8_t type; // cast(CType)
    size_t size;
    void* buffer;
} CArray;

typedef struct CDict {
    size_t size;
    const char** keys;
    CAnyValue** values;
} CDict;

typedef struct CAnyValue {
    uint8_t type; // cast(CType)

    union {
        int64_t m_Int64;
        int32_t m_Int32;
        int16_t m_Int16;
        int8_t  m_Int8;

        uint64_t m_Uint64;
        uint32_t m_Uint32;
        uint16_t m_Uint16;
        uint8_t  m_Uint8;

        void* m_Pointer;
        const char* m_String;

        double m_Double;
        float  m_Float;
        bool   m_Bool;

        CAnyArray* m_AnyArray;
        CArray*    m_Array;
        CDict*     m_Dict;
    } value;

} CAnyValue;

typedef struct SDK_AnyValueFactory
{
    CAnyValue* (*MakeInt64Value)(int64_t value);
    CAnyValue* (*MakeInt32Value)(int32_t value);
    CAnyValue* (*MakeInt16Value)(int16_t value);
    CAnyValue* (*MakeInt8Value)(int8_t value);

    CAnyValue* (*MakeUint64Value)(uint64_t value);
    CAnyValue* (*MakeUint32Value)(uint32_t value);
    CAnyValue* (*MakeUint16Value)(uint16_t value);
    CAnyValue* (*MakeUint8Value)(uint8_t value);

    CAnyValue* (*MakeDoubleValue)(double value);
    CAnyValue* (*MakeFloatValue)(float value);
    CAnyValue* (*MakeBoolValue)(bool value);

    CAnyValue* (*MakeNullValue)();
    CAnyValue* (*MakeStringValue)(const char* value);

    CAnyArray* (*MakeAnyArrayValue)(uint32_t size);
} SDK_AnyValueFactory;

END_SDK

#ifdef __cplusplus

template <typename T>
inline T ValueAs(CAnyValue* val) {
    return *(T*)(&val->value.m_Pointer);
}

#endif // __cplusplus

#endif // YAMP_SDK_ANY_VALUE_H
