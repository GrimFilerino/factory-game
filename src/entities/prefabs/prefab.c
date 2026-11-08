#include "player/player.h"
#include "prefab_internal.h"

static PrefabCreateCallback prefabs[PREFAB_COUNT];

static void prefab_register(prefab_t type, PrefabCreateCallback create) {
        if (type >= PREFAB_COUNT) {
                return;
        }

        prefabs[type] = create;
}


void initialize_prefabs(void) {
        prefab_register(PLAYER, player_create);
        //prefab_register(WALL, wall_create);
}

void prefab_create(prefab_t type, char* uuid, float x, float y) {
        if (type >= PREFAB_COUNT || !prefabs[type]) {
                return;
        }

        return prefabs[type](uuid, x, y);
}
