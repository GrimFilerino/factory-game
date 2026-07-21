#include "health.h"
#include "../../../hashmap/hashmap.h"
#include <stdio.h>

Hashmap* healths;

void initialize_health(char* entityId, float health, float max_health) {
       
        if(healths == NULL) {
                healths = create_hash_map();
        }
        

        //check if the entity already has been initialized, if so just return 
        health_t* entity_health = hash_map_get(healths, entityId);
        if(entity_health) {
                return;
        }


        //otherwise initialize it
        entity_health = malloc(sizeof(health_t));
        if(!entity_health) {
                return;
        }

        printf("healths = %p\n", (void *)healths);
        printf("entityId = %s\n", entityId);
        printf("entity_health = %p\n", (void *)entity_health);
        
        entity_health->max_health = max_health;
        entity_health->current_health = health;

        hash_map_add(healths, entityId, entity_health);
}

void set_max_health(char* entityId, float new_max_health) {
        health_t* entity_health = hash_map_get(healths, entityId);

        if(!entity_health) {
                return;
        }
        
        entity_health->max_health = new_max_health;
}

void adjust_health(char* entityId, float amount) {
        health_t* entity_health = hash_map_get(healths, entityId);

        if(!entity_health) {
                return;
        }

        entity_health->current_health += amount;
}

float get_health(char* entityId) {
        health_t* entity_health = hash_map_get(healths, entityId);

        if(!entity_health) {
                return 0;
        }
        
        return entity_health->current_health;
}
