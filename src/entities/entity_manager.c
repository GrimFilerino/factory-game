#include "entity_manager.h"
#include "components/aabb/aabb.h"
#include "components/camera/camera.h"
#include "components/damage/damage.h"
#include "components/health/health.h"
#include "components/input/input.h"
#include "components/sprite/sprite.h"
#include "components/transform/transform.h"
#include "../logger/logger.h"
#include "entity.h"
#include <string.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

entity_t** entities;

unsigned char entity_index = 0;

static char* uuid() {
        char v[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        char* buf = malloc(37); 

        for(int i = 0; i < 36; ++i) {
                buf[i] = v[arc4random_uniform(16)];
        }

        buf[8] = '-';
        buf[13] = '-';
        buf[18] = '-';
        buf[23] = '-';
        buf[36] = '\0';

        return buf;
}

static entity_t* get_entity_by_id(char* id) {
        for(int i = 0; i <  sizeof(entities); i++) {
                entity_t* e = entities[i];
                if(e->id == id){
                        return e;
                }
        }

        return NULL;
}

void initialize_entity_manager(void) {
        entities = calloc(MAX_ENTITIES, 8);
}

void create_entity(entities_t type) {
        switch(type) {
                case PLAYER : {
                        entity_t* player = malloc(sizeof(*player));
                        
                        *player = (entity_t){
                                .type = type,
                                .id = uuid(),
                                .is_alive = 1,
                                .has_transform = 1,
                                .has_sprite = 1,
                                .has_health = 1,
                                .has_input = 1,
                                .has_aabb = 1,
                                .has_damage = 1,
                        };

                        if(entity_index == MAX_ENTITIES) {
                                create_log(ERROR, "Max entities was reached and no more entities can be created!");
                                return;
                        }

                        initialize_transform(player->id, (vec2_t){ .x = 20, .y = 20}, 50.0f, false);
                        
                        char path[1024];
                        snprintf(path, sizeof(path), "%sassets/player.png", GetApplicationDirectory());
                        initialize_sprite(player->id, path, 20, 20);

                        bind_input(MOVE_UP,     KEY_W); 
                        bind_input(MOVE_DOWN,   KEY_S); 
                        bind_input(MOVE_LEFT,   KEY_A); 
                        bind_input(MOVE_RIGTH,  KEY_D); 

                        initialize_aabb(player->id, 20, 20);

                        initialize_damage(player->id, 15.0f, 0.0f);

                        initialize_health(player->id, 100.0f, 100.0f);

                        switch_entity_to_trace(player->id); 

                        entities[entity_index] = player;
                        entity_index++;
                        
                        break;
                }

                case WALL: {
                        entity_t* wall = malloc(sizeof(*wall));
                        
                        *wall = (entity_t){
                                .type = type,
                                .id = uuid(),
                                .is_alive = 1,
                                .has_transform = 1,
                                .has_sprite = 1,
                                .has_health = 0,
                                .has_input = 0,
                                .has_aabb = 1,
                                .has_damage = 0,
                        };

                        if(entity_index == MAX_ENTITIES) {
                                create_log(ERROR, "Max entities was reached and no more entities can be created!");
                                return;
                        }

                        initialize_transform(wall->id, (vec2_t){ .x = 120, .y = 120}, 0.0f, true);
                        
                        char path[1024];
                        snprintf(path, sizeof(path), "%sassets/wall.png", GetApplicationDirectory());
                        initialize_sprite(wall->id, path, 32, 32);

                        initialize_aabb(wall->id, 32, 32);

                        entities[entity_index] = wall;
                        entity_index++;

                        break;
                }
        } 
}



void update_entities(void){
        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* e = entities[i];
                if(e->has_transform) {
                        if(e->has_input) { 
                                handle_input(e->id);
                        }

                        if(e->has_aabb) {
                                for(unsigned short k = 0; k < entity_index; k++) {
                                        entity_t* b = entities[k];
                                        
                                        if(strcmp(e->id, b->id) == 0) {
                                                continue;
                                        }

                                        if(!b->has_transform || distance_between_entities(e->id, b->id) > 100.0f) {
                                                continue;
                                        }

                                        //check collision and do correction as well in the same pass if entity is not static
                                        if (check_collison(e->id, b->id)){
                                                //do damage if enemy
                                        }
                                }
                        }
                }
        }

        trace_entity_with_camera();
}

void destroy_entities(void){
        //TODO add this :D
}


void draw_entities(void) {
        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* e = entities[i];
                if(e->has_sprite && e->has_transform) {
                        draw_sprite(e->id);
                }
        }
}
