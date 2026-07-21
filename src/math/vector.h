#ifndef VECTOR_H 
#define VECTOR_H

#include <stdbool.h>

typedef struct vec2 {
        float x;
        float y;
} vec2_t;


void set_vector_to_constant(vec2_t* a, float c);
void set_vector(vec2_t* a, vec2_t b);

vec2_t add_vector(vec2_t a, vec2_t b);
vec2_t subtract_vector(vec2_t a, vec2_t b);

vec2_t multiply_vector(vec2_t a, vec2_t b);
vec2_t multiply_constant(vec2_t a, float c);

vec2_t divide_vector(vec2_t a, vec2_t b);
vec2_t divide_constant(vec2_t a, float c);

vec2_t sqrt_vector(vec2_t a);

vec2_t normalize_vector(vec2_t a);
vec2_t normalize_vector_scale(vec2_t a, float s);

float distance_between_vectors(vec2_t a, vec2_t b);

bool is_distance_less(vec2_t a, vec2_t b, float distance);
bool is_distance_more(vec2_t a, vec2_t b, float distance);

#endif
