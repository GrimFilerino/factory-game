#ifndef SPRITE_H
#define SPRITE_H

#include "../../../math/vector.h"

typedef struct sprite {
        vec2_t size;
        vec2_t frame_position;
        unsigned short texture_id;
        unsigned short animation_index; 
} sprite_t;

sprite_t* create_sprite(vec2_t size, unsigned short texture_id);

void draw_sprite(sprite_t* sprite, vec2_t* pos);

#endif
