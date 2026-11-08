#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../hashmap/hashmap.h"
#include "./components/components.h"
#include "prefabs/prefab.h"

typedef struct entity {
        char* id;
        bool is_alive;
        prefab_t type;
} entity_t;


void initialize_entity_manager(void);

void create_entity(prefab_t type, float x, float y);

void update_entities(void);

void destroy_entities(void);

void draw_entities(void);

#endif
