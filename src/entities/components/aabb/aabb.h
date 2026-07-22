#ifndef AABB_H
#define AABB_H

#include "../../../math/vector.h"
#include <stdbool.h>

typedef struct aabb {
        vec2_t half_size;
        vec2_t size;
        vec2_t offset;
} aabb_t;

void initialize_aabb(char* entity_id, float width, float height, float x_offset, float y_offset);
bool check_collison(char* entity_id_a, char* entity_id_b);
aabb_t* get_aabb_component(char* entity_id);

#endif

