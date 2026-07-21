#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "../hashmap/hashmap.h"
#include "./components/components.h"

#define MAX_ENTITIES 255

void initialize_entity_manager(void);

void create_entity(entities_t type);

void update_entities(void);

void destroy_entities(void);

void draw_entities(void);

#endif



//char** get_entities_by_type(entities_t type);
//
/*char** get_entities_by_type(entities_t type) {
        if(!entities) {
                return NULL;
        }

        char** entity_ids = calloc(4, sizeof(char*));

        int index = 0;
        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* e = entities[i];
                if(e->type == type) {
                        if(sizeof(entity_ids) <= index) {
                                entity_ids = reallocarray(entity_ids, index * 2, sizeof(char*));
                        }

                        entity_ids[index] = e->id;
                        index++;
                }
        }

        entity_ids = reallocarray(entity_ids, index, sizeof(char*));

        return entity_ids;
}*/
