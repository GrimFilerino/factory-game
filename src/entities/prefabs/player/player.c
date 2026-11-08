#include "player.h"

Entity player_create(char* uuid, float x, float y) {

        initialize_transform(uuid, (vec2_t){.x = 20, .y = 20}, 50.0f, false);

        initialize_sprite(uuid, "assets/player.png", 20, 20);

        initialize_aabb(uuid, 20, 20, 0, 0);

        initialize_damage(uuid, 15.0f, 0.0f);

        initialize_health(uuid, 100.0f, 100.0f);

        switch_entity_to_trace(uuid);
}

/*snprintf(path, sizeof(path), "%sassets/player.png", GetApplicationDirectory());*/
