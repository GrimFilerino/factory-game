#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "../hashmap/hashmap.h"
#include "./components/components.h"

#define MAX_ENTITIES 255

void initialize_entity_manager(void);

void create_entity(entities_t type);

void add_component_to_entity(char* id, components_t component, void* data);

char** get_entities_by_type(entities_t type);

void remove_component_from_entity(char* id, components_t component);

void update_entities(void);

void destroy_entities(void);

void draw_entities(void);

#endif
