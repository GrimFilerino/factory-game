#include "entity_manager.h"
#include "components/components.h"
#include "prefabs/prefab_internal.h"
#include <string.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

Music music;

entity_t** entities;
unsigned char entity_index = 0;

void initialize_entity_manager(void) {
        SetMasterVolume(100);
        initialize_sounds();

        bind_input(MOVE_UP,     KEY_W); 
        bind_input(MOVE_DOWN,   KEY_S); 
        bind_input(MOVE_LEFT,   KEY_A); 
        bind_input(MOVE_RIGTH,  KEY_D);
        bind_input(ATTACK,      KEY_F);


        char path[1024];
        snprintf(path, sizeof(path), "%sassets/music/music.mp3", GetApplicationDirectory());
        music = LoadMusicStream(path);

        if(!IsMusicStreamPlaying(music)) {
                PlayMusicStream(music);
        }

}

void create_entity(prefab_t type, float x, float y) {
        int entityId = entity_index;
        char str[255];
        sprintf(str, "%d", entityId);
        prefab_create(type, (char*)str,x, y);

        entity_t* new_entity = malloc(sizeof(entity_t));
        if(new_entity == NULL) {
                return;
        }

        *new_entity = (entity_t){
                .id = str,
                .is_alive = true,
                .type = type
        };

        entities[++entity_index] = new_entity;
}

void update_entities(void) {
        SetMusicVolume(music, 0.1);
        UpdateMusicStream(music);

        for(unsigned short i = 0; i < entity_index; i++) {
                entity_t* entity_a = entities[i];
                if(has_component(entity_a->id, COMPONENT_TRANSFORM)) {
                        if(has_component(entity_a->id, COMPONENT_INPUT)) { 
                                handle_input(entity_a->id);
                        }

                        if(has_component(entity_a->id, COMPONENT_AABB)) {
                                for(unsigned short k = 0; k < entity_index; k++) {
                                        entity_t* entity_b = entities[k];
                                        
                                        if(strcmp(entity_a->id, entity_b->id) == 0) {
                                                continue;
                                        }

                                        if(!has_component(entity_b->id, COMPONENT_TRANSFORM) || distance_between_entities(entity_a->id, entity_b->id) > 100.0f) {
                                                continue;
                                        }

                                        //check collision and do correction as well in the same pass if entity is not static
                                        if (check_collison(entity_a->id, entity_b->id)){
                                                //do damage to entity a
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
