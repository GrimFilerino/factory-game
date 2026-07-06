#include "./vector.h"
#include <math.h>

void set_vector_to_constant(vec2_t *a, float c) {
        a->x = c;
        a->y = c;
}

void set_vector(vec2_t *a, vec2_t b) { *a = b; }

vec2_t add_vector(vec2_t a, vec2_t b) {
        return (vec2_t){.x = a.x + b.x, .y = a.y + b.y};
}
vec2_t subtract_vector(vec2_t a, vec2_t b) {
        return (vec2_t){.x = a.x - b.x, .y = a.y - b.y};
}

vec2_t multiply_vector(vec2_t a, vec2_t b) {
        return (vec2_t){.x = a.x * b.x, .y = a.y * b.y};
}
vec2_t scale_vector(vec2_t a, float c) {
        return (vec2_t){.x = a.x * c, .y = a.y * c};
}

vec2_t divide_vector(vec2_t a, vec2_t b) {
        return (vec2_t){.x = a.x / b.x, .y = a.y / b.y};
}
vec2_t divide_constant(vec2_t a, float c) {
        return (vec2_t){.x = a.x / c, .y = a.y / c};
}

vec2_t sqrt_vector(vec2_t a) {
        return (vec2_t){.x = (float)sqrt(a.x), .y = (float)sqrt(a.y)};
}

vec2_t normalize_vector(vec2_t a) {
        float length = sqrt(a.x * a.x + a.y * a.y);
        if(length == 0){
                return (vec2_t){.x = 0, .y = 0 };
        }

        return (vec2_t){.x = a.x / length, .y = a.y / length };
}

vec2_t normalize_vector_scale(vec2_t a, float s) {
        return scale_vector(normalize_vector(a), s); 
}
