#ifndef AABB_H
#define AABB_H

#include "../../../math/vector.h"

typedef struct aabb {
        vec2_t size;
        vec2_t half_size;
} aabb_t;

#endif

