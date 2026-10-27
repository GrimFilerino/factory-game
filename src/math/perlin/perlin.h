#ifndef PERLIN_H
#define PERLIN_H

void set_seed(int seed);
float perlin_2d(float x, float y, float freq, int depth, float amp);

#endif
