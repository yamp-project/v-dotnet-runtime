#ifndef YAMP_SDK_CONTEXT_H
#define YAMP_SDK_CONTEXT_H

#include "sdk_interface.h"

BEGIN_SDK

typedef struct SDK_Context
{
    const char* version;
    const char* sdkVersion;

    // lifecycle
    bool (*Init)();
    void (*Shutdown)();

    // events
    void (*OnResourceStart)(SDK_Resource* resource);
    void (*OnResourceStop)(SDK_Resource* resource);
    void (*OnTick)();
    void (*OnCoreEvent)(CoreEventType eventType, CAnyArray* args);
    void (*OnResourceEvent)(const char* eventName, CAnyArray* args);
} SDK_Context;

typedef SDK_Interface* (*RegisterRuntime)(const char* identifier, SDK_Context context);

END_SDK

#endif // YAMP_SDK_CONTEXT_H
