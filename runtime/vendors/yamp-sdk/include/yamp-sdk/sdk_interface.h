#ifndef YAMP_SDK_INTERFACE_H
#define YAMP_SDK_INTERFACE_H

#include "sdk_common.h"

#include "game/sdk_natives.h"
#include "game/sdk_entity.h"
#include "game/sdk_player.h"
#include "game/sdk_events.h"

#include "misc/sdk_any_value.h"
#include "misc/sdk_resource.h"

BEGIN_SDK

typedef struct SDK_Interface
{
    const SDK_EntityApi* entityApi;

    SDK_AnyValueFactory* anyValueFactory;
    SDK_NativesFactory* nativesFactory;

    // Entity for now, we will add LocalPlayer later on
    SDK_Entity* (*GetLocalPlayer)();

    void (*LogDebug)(const char* fmt, ...);
    void (*LogInfo) (const char* fmt, ...);
    void (*LogWarn) (const char* fmt, ...);
    void (*LogError)(const char* fmt, ...);

    CoreEventMetas (*GetCoreEventMetas)();
    void (*GetCoreEventArgs)();
    void (*EmitResourceEvent)(const char* eventName, CAnyArray* args);
} SDK_Interface;

END_SDK

#endif // YAMP_SDK_INTERFACE_H
