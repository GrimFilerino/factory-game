#include "aabb.h"
#include "../../../hashmap/hashmap.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

Hashmap* aabbs;

void initialize_aabb(char* entity_id, float width, float height){
        aabb_t* aabb = malloc(sizeof(aabb_t));        
        if(!aabb) {
                return;
        }

        if(aabbs == NULL ){
                aabbs = create_hash_map();
        }

        if(hash_map_get(aabbs, entity_id) != NULL) {
                return;
        }

        aabb->half_size->x = width/2;
        aabb->half_size->y = height/2;
        aabb->size->x = width;
        aabb->size->y = height;

        hash_map_add(aabbs, entity_id, aabb);
}


bool check_collison(vec2_t* a, vec2_t* b, char* entity_id_a, char* entity_id_b) {
        aabb_t* aabb_a = hash_map_get(aabbs, entity_id_a);
        aabb_t* aabb_b = hash_map_get(aabbs, entity_id_b);

        if(!aabb_a || !aabb_b) {
                return false;
        }

        float center_a_x = a->x + aabb_a->half_size->x;
        float center_a_y = a->y + aabb_a->half_size->y; 

        float center_b_x = b->x + aabb_b->half_size->x; 
        float center_b_y = b->y + aabb_b->half_size->y;

        float overlap_x = (aabb_a->half_size->x + aabb_b->half_size->x) - fabsf((center_a_x - center_b_x));
        float overlap_y = (aabb_a->half_size->y + aabb_b->half_size->y) - fabsf((center_a_y - center_b_y));

        if(overlap_x > 0 && overlap_y > 0) {
                
                if(overlap_x < overlap_y) {
                        a->x += center_a_x > center_b_x ? overlap_x : -overlap_x;
                } else {
                        a->x += center_a_y > center_b_y ? overlap_y : -overlap_y;
                }
               
                return true;
        }

        return false;
}
