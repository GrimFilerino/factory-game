#ifndef SPRITE_H
#define SPRITE_H

#include "../../../math/vector.h"

typedef struct sprite {
        vec2_t size;
        vec2_t frame_position;
        unsigned short animation_index; 
        unsigned int texture_id;
} sprite_t;

void initialize_sprite(char* id, char* filepath, float width, float height);
unsigned int add_texture(char* filename);
void draw_sprite(char* entity_id);

#endif
