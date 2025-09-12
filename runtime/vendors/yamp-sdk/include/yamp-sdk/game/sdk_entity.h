#ifndef YAMP_SDK_GAME_ENTITY_H
#define YAMP_SDK_GAME_ENTITY_H

#include "yamp-sdk/sdk_common.h"

BEGIN_SDK

typedef struct sdk_entity_t SDK_Entity;

typedef struct SDK_EntityApi
{
    float (*GetHealth)(SDK_Entity* entity);
    void  (*SetHealth)(SDK_Entity* entity, float health);

    float (*GetHeading)(SDK_Entity* entity);
    void  (*SetHeading)(SDK_Entity* entity, float heading);
} SDK_EntityApi;

END_SDK

#endif // YAMP_SDK_GAME_ENTITY_H
