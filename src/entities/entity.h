#ifndef ENTITY_H
#define ENTITY_H


typedef enum entities {
        PLAYER,
        ANT
} entities_t;

typedef struct entity {
        entities_t type;
        char* id;
        unsigned is_alive:1;
        unsigned has_transform:1;
        unsigned has_sprite:1;
        unsigned has_health:1;
        unsigned has_input:1;
        unsigned has_camera:1;
} entity_t;

#endif
