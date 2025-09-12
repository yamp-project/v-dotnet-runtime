#ifndef YAMP_SDK_GAME_EVENTS_H
#define YAMP_SDK_GAME_EVENTS_H

#include "yamp-sdk/sdk_common.h"

BEGIN_SDK

typedef enum CoreEventType
{
    ENTITY_COLLISION,
    WEAPON_FIRE,

#ifdef YAMP_SERVER_SIDE
    PLAYER_CONNECT,
    PLAYER_DISCONNECT,
#endif

    EVENT_COUNT
} CoreEventType;

typedef struct CoreEventMeta
{
    CoreEventType type;
    const char* name;
} CoreEventMeta;

typedef struct CoreEventMetas
{
    size_t size;
    CoreEventMeta* buffer;
} CoreEventMetas;

END_SDK

#endif // YAMP_SDK_GAME_EVENTS_H
