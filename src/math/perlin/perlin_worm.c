#include "perlin_worm.h"
#include "perlin.h"

float perlin_worm(float x, float y) {
        float value = perlin_2d(x, y, 0.5f, 2, 2.0f);

        if(value >= 0.5f) {
                value = 1.0f;
        } else {
                value = 0.0f;
        }

        return value;
}
