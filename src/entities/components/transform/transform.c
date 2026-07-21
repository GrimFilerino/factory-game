#include "transform.h"
#include "../../../hashmap/hashmap.h"
Hashmap* transforms;

void initialize_transform(char* id, vec2_t pos,float movement_speed, bool is_static) {
        transform_t* tf = malloc(sizeof(transform_t));
        
        vec2_t* position = malloc(sizeof(vec2_t));

        if(!position) {
                return;
        }

        vec2_t* velocity = malloc(sizeof(vec2_t));

        if(!velocity) {
                return;
        }

        velocity->x = 0.0f;
        velocity->y = 0.0f;

        position->x = pos.x;
        position->y = pos.y;

        *tf = (transform_t){
                .position = position,
                .velocity = velocity,
                .movement_speed = movement_speed,
                .is_static = is_static
        };

        if(transforms == NULL) {
               transforms = create_hash_map(); 
        }

        hash_map_add(transforms, id, tf);
}

void apply_uniformed_velocity(char* entity_id) {
        transform_t* transform = hash_map_get(transforms, entity_id);
        
        if(!transform) {
                return;
        }

        if(transform->is_static) {
                return;
        }

        transform->position->y += transform->velocity->y;
        transform->position->x += transform->velocity->x;

        transform->velocity->x = 0.0f;
        transform->velocity->y = 0.0f;
}

transform_t* get_transform_component(char* entity_id) {
        return hash_map_get(transforms, entity_id);
}

float distance_between_entities(char *entity_a_id, char *entity_b_id) {
        transform_t* a = hash_map_get(transforms, entity_a_id);
        transform_t* b = hash_map_get(transforms, entity_b_id);

        return distance_between_vectors(*a->position, *b->position);
}
