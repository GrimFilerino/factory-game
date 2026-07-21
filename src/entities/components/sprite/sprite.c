#include "sprite.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../hashmap/hashmap.h"
#include "../transform/transform.h"

Hashmap* textures;
Hashmap* sprites;

void initialize_sprite(char* id, char* filepath, float width, float height) {
        sprite_t* spr = malloc(sizeof(sprite_t));
       
        unsigned int texture_id = add_texture(filepath);

        *spr = (sprite_t){
                .size = (vec2_t){ .x = width, .y = height },
                .frame_position = 0,
                .texture_id = texture_id,
                .animation_index = 0 
        };

        if(sprites == NULL) {
                sprites = create_hash_map();
        }

        hash_map_add(sprites, id, spr);
}


unsigned int add_texture(char* filename) {
        Texture2D* texture = malloc(sizeof(Texture2D));
        if(!texture) {
                return 0;
        }

        if(textures == NULL) {
                textures = create_hash_map();
        }

        printf("Loading: %s\n", filename);
        *texture = LoadTexture(filename);

        if (texture->id == 0) {
                printf("Failed to load texture: %s\n", filename);
                free(texture);
                return 0;
        }

        char* str_id = calloc(256, sizeof(char));
        sprintf(str_id, "%d", texture->id);

        hash_map_add(textures, str_id, (void*)texture);

        return texture->id;
}


void draw_sprite(char* entity_id) {
        sprite_t* sprite = hash_map_get(sprites, entity_id);
        transform_t* transform = get_transform_component(entity_id);

        if(!transform || !sprite) {
                printf("nerf \n");
                return;
        }

        char str_id[256];
        sprintf(str_id, "%d", sprite->texture_id);
        Texture2D* texture = hash_map_get(textures, str_id);

        if (texture == NULL) {
                printf("Texture %u not found!\n", sprite->texture_id);
                return;
        }

        DrawTextureV(*texture, (Vector2){ transform->position->x, transform->position->y}, WHITE);
}
