#ifndef YAMP_SDK_RESOURCE_H
#define YAMP_SDK_RESOURCE_H

#include "yamp-sdk/sdk_common.h"

BEGIN_SDK

typedef struct SDK_Resource
{
    const char* name;
    const char* type;
    const char* path;
    const char* mainFile;
} SDK_Resource;

END_SDK

#endif // YAMP_SDK_RESOURCE_H
