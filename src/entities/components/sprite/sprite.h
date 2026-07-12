#ifndef SPRITE_H
#define SPRITE_H

#include "../../../math/vector.h"

typedef struct sprite {
        vec2_t size;
        vec2_t frame_position;
        unsigned short animation_index; 
        unsigned int texture_id;
} sprite_t;

unsigned int add_texture(char* filename);

void draw_sprite(sprite_t* sprite, vec2_t* pos);

#endif
