#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

typedef enum entities {
        PLAYER,
        WALL 
} entities_t;

typedef struct entity {
        entities_t type;
        char* id;
        bool is_alive;
        bool has_transform;
        bool has_sprite;
        bool has_health;
        bool has_input;
        bool has_aabb;
        bool has_damage;
} entity_t;

#endif
