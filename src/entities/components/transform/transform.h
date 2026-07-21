#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../../../math/vector.h"
#include <stdbool.h>

typedef struct transfrom {
        vec2_t* velocity;
        vec2_t* position;
        bool    is_static;
        float   movement_speed;
} transform_t;


void initialize_transform(char* id, vec2_t pos, float movement_speed, bool is_static);
void apply_uniformed_velocity(char* entity_id);
transform_t* get_transform_component(char* entity_id);

float distance_between_entities(char* entity_a_id, char* entity_b_id);

#endif
