#ifndef WORLD_GENERATION_H  
#define WORLD_GENERATION_H

#include "../../../../math/vector.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16 
#define TILE_SIZE 16
#define CHUNK_MAX_TILE_AMOUNT (CHUNK_WIDTH * CHUNK_HEIGHT)

typedef enum biome {
        PLAINS,
        OCEAN
} biome_t;

typedef enum tile_type {
        GRASS,
        STONE,
        WATER
} tile_t;


typedef struct tile_data {
        tile_t tile_type;
        float perlin_noise_value;
} tile_data_t;

typedef struct world_chunk {
        vec2_t origin_pos;
        biome_t biome;
        tile_data_t tile_data[CHUNK_MAX_TILE_AMOUNT]; 
} world_chunk_t;

#endif  
