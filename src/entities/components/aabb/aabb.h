#ifndef AABB_H
#define AABB_H

#include "../../../math/vector.h"
#include <stdbool.h>

typedef struct aabb {
        vec2_t half_size;
        vec2_t size;
} aabb_t;

void initialize_aabb(char* entity_id, float width, float height);
bool check_collison(char* entity_id_a, char* entity_id_b);
aabb_t* get_aabb_component(char* entity_id);

#endif

