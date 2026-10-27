#include "world_generation.h"
#include "../../../../hashmap/hashmap.h"
#include "../../../../math/perlin/perlin.h"
#include "../../../../math/perlin/perlin_worm.h"
#include <stdio.h>
#include <stdlib.h>


Hashmap* chunks;

/**
 * Get tile data at tile position on chunk
 */
static tile_data_t get_tile_at(tile_data_t* tile_data[], int cell_x, int cell_y) {
        return *tile_data[cell_y * CHUNK_WIDTH + cell_x];
}

/**
 * Get tile data at tile position on chunk
 */
static void set_tile_at(tile_data_t* tile_data[], int cell_x, int cell_y, tile_t tile_value, float noise_value) {
        tile_data[cell_y * CHUNK_WIDTH + cell_x]->tile_type             = tile_value;
        tile_data[cell_y * CHUNK_WIDTH + cell_x]->perlin_noise_value    = noise_value;
}

/**
 *  Returns a formatted string for hashmap, format is xcord_ycord
 */
static char* get_chunk_key(vec2_t origin_pos) {
        char* key = malloc(256);
        
        if(key == NULL) {
                return "";
        }

        sprintf(key, "%g_%g", origin_pos.x, origin_pos.y);
        return key;
}

static tile_t get_tile_type(float tile_noise_value, biome_t* biome) {
        return GRASS;
}

static float lerp(float a, float b, float t){
        return a + (b - a) * t;
}

float determine_chunk_biome_value(vec2_t* chunk_pos) {
        //not sure if this works and if this is how you should do it...
        float valueOne      = perlin_2d(chunk_pos->x, chunk_pos->y, 1.0f,  2, 2.5f);
        float valueTwo      = perlin_2d(chunk_pos->x, chunk_pos->y, 0.23f, 4, 2.0f);
        float valueThree    = perlin_2d(chunk_pos->x, chunk_pos->y, 0.65f, 3, 1.226f);
        float valueFour     = perlin_2d(chunk_pos->x, chunk_pos->y, 1.0f,  6, 1.245);

        float lerpOne =     lerp(valueOne,   valueTwo,  0.356);
        float lerpTwo =     lerp(valueThree, valueFour, 0.52);
        float biome_value = lerp(lerpOne,    lerpTwo,   0.392);

        return biome_value;
}

biome_t* determine_chunk_biome(float tile_noise_value, float biome_value) {
        int* biome = malloc(sizeof(int));

        if(!biome) {
                return NULL;
        }

        *biome = OCEAN;

        if(tile_noise_value > 0.269f) {
                       
        }


        return (biome_t*)biome;
}

static void generate_chunk_tile_data(world_chunk_t* chunk) {
        for(int x = 0; x < CHUNK_WIDTH; x++) {
                for(int y = 0; y < CHUNK_HEIGHT; y++) {
                        // get tile data which could be NULL if not generated yet
                        tile_data_t data = get_tile_at(chunk->tile_data, x, y);
                        float tile_noise_value = data.perlin_noise_value;

                        if(!tile_noise_value) {
                                //convert to ints to get exakt tile origin for perlin noise generation
                                int noise_x = (int)(chunk->origin_pos->x + x * TILE_SIZE);
                                int noise_y = (int)(chunk->origin_pos->y + y * TILE_SIZE);

                                // get perlin worm to generate lakes and rivers first
                                tile_noise_value = perlin_worm(noise_x, noise_y);

                                // if the value is 1.0f then we know we are working with land and therefore should lerp two noise maps for terrain
                                // otherwise it will remain 0.0f which will be water always!
                                if(tile_noise_value > 0.0f) {
                                        float terrain_value_one = perlin_2d(noise_x, noise_y, 2.0f, 4, 2.0f);
                                        float terrain_value_two = perlin_2d(noise_x, noise_y, 0.5f, 2, 1.1f);
                                        tile_noise_value = lerp(terrain_value_one, terrain_value_two, 0.45);
                                } 

                                float biome_value = determine_chunk_biome_value(chunk->origin_pos);
                                chunk->biome = determine_chunk_biome(tile_noise_value, biome_value); 
                                tile_t tile = get_tile_type(tile_noise_value, chunk->biome);
                                
                                //save it on the chunks heap allocated tile_data array
                                set_tile_at(chunk->tile_data, x, y, tile, tile_noise_value);
                        }

                }
        }
}



static world_chunk_t* create_chunk(vec2_t origin_pos) {
        world_chunk_t* chunk = malloc(sizeof(world_chunk_t));
        if(chunk == NULL){
                return NULL;
        }

        chunk->origin_pos = origin_pos;

        *chunk->tile_data = calloc(CHUNK_MAX_TILE_AMOUNT, sizeof(tile_data_t));
        if(*chunk->tile_data == NULL) {
                return NULL;
        }

        generate_chunk_tile_data(chunk);

        return chunk;
}




void init() {
        chunks = create_hash_map();
}




