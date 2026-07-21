#include "aabb.h"
#include "../../../hashmap/hashmap.h"
#include "../transform/transform.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

Hashmap* aabbs;

void initialize_aabb(char* entity_id, float width, float height){
        aabb_t* aabb = malloc(sizeof(aabb_t));        
        if(!aabb) {
                return;
        }

        if(aabbs == NULL){
                aabbs = create_hash_map();
        }


        aabb->half_size.x = width/2;
        aabb->half_size.y = height/2;
        aabb->size.x = width;
        aabb->size.y = height;

        hash_map_add(aabbs, entity_id, aabb);
}


bool check_collison(char* entity_id_a, char* entity_id_b) {
        transform_t* transform_a = get_transform_component(entity_id_a);
        transform_t* transform_b = get_transform_component(entity_id_b);
        aabb_t* aabb_a = hash_map_get(aabbs, entity_id_a);
        aabb_t* aabb_b = hash_map_get(aabbs, entity_id_b);

        vec2_t* a = transform_a->position; 
        vec2_t* b = transform_b->position; 

        if(!aabb_a || !aabb_b) {
                return false;
        }

        float center_a_x = a->x + aabb_a->half_size.x;
        float center_a_y = a->y + aabb_a->half_size.y; 

        float center_b_x = b->x + aabb_b->half_size.x; 
        float center_b_y = b->y + aabb_b->half_size.y;

        float overlap_x = (aabb_a->half_size.x + aabb_b->half_size.x) - fabsf((center_a_x - center_b_x));
        float overlap_y = (aabb_a->half_size.y + aabb_b->half_size.y) - fabsf((center_a_y - center_b_y));

        if(overlap_x > 0 && overlap_y > 0) {
              
                //do not correct if the colliding object is static
                // check that player collided with wall do correction
                // check that wall collided with player do not push back wall (wall is static entity)
                if(!transform_a->is_static) {
                        if(overlap_x < overlap_y) {
                                a->x += center_a_x > center_b_x ? overlap_x : -overlap_x;
                        } else {
                                a->y += center_a_y > center_b_y ? overlap_y : -overlap_y;
                        }
                }
               
                return true;
        }

        return false;
}

aabb_t* get_aabb_component(char* entity_id) {
        return hash_map_get(aabbs, entity_id);
}
