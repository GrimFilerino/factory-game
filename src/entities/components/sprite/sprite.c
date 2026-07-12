#include "sprite.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../hashmap/hashmap.h"

Hashmap* textures;

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


void draw_sprite(sprite_t *sprite, vec2_t *pos) {
        char str_id[256];
        sprintf(str_id, "%d", sprite->texture_id);
        Texture2D* texture = hash_map_get(textures, str_id);

        if (texture == NULL) {
                printf("Texture %u not found!\n", sprite->texture_id);
                return;
        }

        DrawTexture(*texture, pos->x, pos->y, WHITE);
}
