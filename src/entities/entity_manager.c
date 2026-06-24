#include "entity_manager.h"
#include "components/components.h"
#include "components/sprite/sprite.h"
#include "components/transform/transform.h"
#include "../logger/logger.h"
#include "entity.h"
#include <raylib.h>
#include <stdlib.h>

entity_t** entities;
Hashmap* transform;
Hashmap* sprite;
Hashmap* health;
Hashmap* input;
Hashmap* camera;

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

static void add_transform(char* id, vec2_t pos) {
        transform_t* tf = malloc(sizeof(*tf));

        *tf = (transform_t){
                .position = &pos,
                .velocity = &(vec2_t) {
                        .x = 0,
                        .y = 0,
                }
        }; 

        hash_map_add(transform, id, tf);
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
        entities = calloc(MAX_ENTITIES, 8); //just an array of pointers....
        
        //create component hash-maps here
        transform = create_hash_map();
        sprite = create_hash_map();
        health = create_hash_map();
        input = create_hash_map();
        camera = create_hash_map();
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
                                .has_camera = 1,
                        };

                        if(entity_index == MAX_ENTITIES) {
                                create_log(ERROR, "Max entities was reached and no more entities can be created!");
                                return;
                        }

                        add_transform(player->id, (vec2_t){ .x = 0, .y = 0});

                        entities[entity_index] = player;
                        entity_index++;
                        
                        break;
                }

                case ANT: {
                        //ANT CODE (HOSTILE MOB) 
                        break;
                }
        } 
}

void add_component_to_entity(char* id, components_t component, void* data) {
        switch (component) {
                case TRANSFORM:
                break;
                
                case CAMERA:
                        entity_t* e = get_entity_by_id(id);
                        if(e != NULL) {
                                e->has_camera = true;

                                //Data should be a Camera2D pointer
                                hash_map_add(camera, e->id, data);
                        } else {
                               //TODO add logger to catch error here
                               create_log(ERROR, "Tried to add camera to entity but entity does not exist");
                        }
                break;
        }
}

void remove_component_from_entity(char* id, components_t component) {
             switch (component) {
                case TRANSFORM:
                break;
                
                case CAMERA:
                        entity_t* e = get_entity_by_id(id);

                        if(e != NULL) {
                                e->has_camera = false;
                                hash_map_remove(camera, id)
                        } else {
                               //TODO add logger to catch error here
                               create_log(WARNING, "Tried to remove camera from entity but entity does not exist");
                        }
                break;
        }   
}

char** get_entities_by_type(entities_t type) {
        char** entity_ids = calloc(4, sizeof(char*));

        int index = 0;
        for(unsigned short i = 0; i <  sizeof(entities); i++) {
                entity_t* e = entities[i];
                if(e->type == type) {
                        if(sizeof(entity_ids) < index) {
                                entity_ids = reallocarray(entity_ids, index * 2, sizeof(char*));
                        }

                        entity_ids[index] = e->id;
                }
        }

        entity_ids = reallocarray(entity_ids, index, sizeof(char*));

        return entity_ids;
}

void update_entities(void){
        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* e = entities[i];
                if(e->has_transform) {
                        transform_t* e_transform = hash_map_get(transform, e->id);

                        if(e->has_input) {
                                
                        }

                        if(e->has_camera) {
                                //Camera trace entity
                                Camera2D* e_camera = hash_map_get(camera, e->id);
                                if(e_camera){
                                        e_camera->target = (Vector2){ 
                                                .x = e_transform->position->x, 
                                                .y = e_transform->position->y 
                                        };
                                }
                        }
                }
        }
}

void destroy_entities(void){

}


void draw_entities(void) {
        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* e = entities[i];
                if(e->has_sprite && e->has_transform) {
                       sprite_t* e_sprite = hash_map_get(sprite, e->id); 
                }
        }
}
