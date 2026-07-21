#include "entity_manager.h"
#include "components/components.h"
#include "components/input/input.h"
#include "components/sprite/sprite.h"
#include "components/transform/transform.h"
#include "../logger/logger.h"
#include "entity.h"
#include <raylib.h>
#include <stdio.h>
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


static void add_sprite(char* id, char* filepath, float width, float height) {
        sprite_t* spr = malloc(sizeof(sprite_t));
       
        unsigned int texture_id = add_texture(filepath);

        *spr = (sprite_t){
                .size = (vec2_t){ .x = width, .y = height },
                .frame_position = 0,
                .texture_id = texture_id,
                .animation_index = 0 
        };

        hash_map_add(sprite, id, spr);
}

static void add_transform(char* id, vec2_t pos) {
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
                .velocity = velocity
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

                        add_transform(player->id, (vec2_t){ .x = 120, .y = 120});
                        
                        char path[1024];
                        snprintf(path, sizeof(path), "%sassets/player.png", GetApplicationDirectory());

                        add_sprite(player->id, path, 20, 20);

                        bind_input(MOVE_UP, KEY_W); 
                        bind_input(MOVE_DOWN, KEY_S); 
                        bind_input(MOVE_LEFT, KEY_A); 
                        bind_input(MOVE_RIGTH, KEY_D); 

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
        entity_t* e = get_entity_by_id(id);

        switch (component) {
                case TRANSFORM:
                break;
                
                case CAMERA:
                        if(e != NULL) {
                                e->has_camera = true;

                                //Data should be a Camera2D pointer
                                hash_map_add(camera, e->id, data);
                        } else {
                               create_log(ERROR, "Tried to add camera to entity but entity does not exist");
                        }
                break;

                case INPUT:
                        if(e != NULL) {
                                
                        } else {
                                create_log(ERROR, "Tried to add camera to entity but entity does not exist");
                        } 
                break;
        }
}

void remove_component_from_entity(char* id, components_t component) {
        switch (component) {
                case TRANSFORM:
                break;
                
                case CAMERA: {
                        entity_t* e = get_entity_by_id(id);

                        if(e != NULL) {
                                e->has_camera = false;
                                hash_map_remove(camera, id);
                        } else {
                               //TODO add logger to catch error here
                               create_log(WARNING, "Tried to remove camera from entity but entity does not exist");
                        }
                        break;
                }
        }   
}

char** get_entities_by_type(entities_t type) {
        if(!entities) {
                return NULL;
        }

        char** entity_ids = calloc(4, sizeof(char*));

        int index = 0;
        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* e = entities[i];
                if(e->type == type) {
                        if(sizeof(entity_ids) <= index) {
                                entity_ids = reallocarray(entity_ids, index * 2, sizeof(char*));
                        }

                        entity_ids[index] = e->id;
                        index++;
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
                                handle_input(e, e_transform, 20.0f);
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
        //TODO add this :D
}


void draw_entities(void) {
        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* e = entities[i];
                if(e->has_sprite && e->has_transform) {
                        sprite_t* e_sprite = hash_map_get(sprite, e->id);
                        transform_t* e_transfrom = hash_map_get(transform, e->id);
                        draw_sprite(e_sprite, e_transfrom->position);
                }
        }
}
