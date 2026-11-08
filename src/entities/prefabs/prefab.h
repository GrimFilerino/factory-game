#ifndef PREFAB_H
#define PREFAB_H

#include "../components/aabb/aabb.h"
#include "../components/camera/camera.h"
#include "../components/damage/damage.h"
#include "../components/health/health.h"
#include "../components/input/input.h"
#include "../components/sound/sound.h"
#include "../components/sprite/sprite.h"
#include "../components/transform/transform.h"

typedef enum prefab {
    PLAYER,
    WALL,
    ENEMY,
    PREFAB_COUNT
} prefab_t;

typedef void (*PrefabCreateCallback)(char* uuid, float x, float y);

void initialize_prefabs(void);

#endif
