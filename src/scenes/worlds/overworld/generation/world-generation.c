#include "world-generation.h"
#include "../../../../hashmap/hashmap.h"
#include "../../../../math/perlin/perlin.h"
#include <stdio.h>
#include <stdlib.h>


Hashmap* chunks;

/**
 * Get tile data at tile position on chunk
 */
static tile_data_t get_tile_at(tile_data_t tile_data[], int cell_x, int cell_y) {
        return tile_data[cell_y * CHUNK_WIDTH + cell_x];
}

/**
 * Get tile data at tile position on chunk
 */
static void set_tile_at(tile_data_t tile_data[], int cell_x, int cell_y, tile_t tile_value) {
        tile_data[cell_y * CHUNK_WIDTH + cell_x].tile_type = tile_value;
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

static tile_t get_tile_type(float tile_noise_value, biome_t biome) {
        return GRASS;
}

static void generate_chunk_tile_data(world_chunk_t* chunk) {
        for(int x = 0; x < CHUNK_WIDTH; x++) {
                for(int y = 0; y < CHUNK_HEIGHT; y++) {
                        int noise_x = (int)(chunk->origin_pos.x + x * TILE_SIZE);
                        int noise_y = (int)(chunk->origin_pos.y + y * TILE_SIZE);
                        tile_data_t data = get_tile_at(chunk->tile_data, x, y);
                        float tile_noise_value = 0;

                        if(!data.perlin_noise_value) {
                                tile_noise_value = perlin_2d(noise_x, noise_y, 2.0f, 4, 1.01);
                        } else {
                                tile_noise_value = data.perlin_noise_value;
                        }

                        tile_t tile = get_tile_type(tile_noise_value, chunk->biome);
                }
        }
}

static float lerp(float a, float b, float t){
        return a + (b - a) * t;
}

biome_t determine_chunk_biome(vec2_t chunk_pos) {
        //not sure if this works and if this is how you should do it...
        float valueOne = perlin_2d(chunk_pos.x, chunk_pos.y, 1.23, 2, 1.0);
        float valueTwo = perlin_2d(chunk_pos.x, chunk_pos.y, 1.23, 4, 2.0);
        float valueThree = perlin_2d(chunk_pos.x, chunk_pos.y, 1.23, 3, 0.226);
        float valueFour = perlin_2d(chunk_pos.x, chunk_pos.y, 1.23, 6, 1.245);

        float lerpOne = lerp(valueOne, valueTwo, 0.356);
        float lerpTwo = lerp(valueThree, valueFour, 0.52);

        float biome_value = lerp(lerpOne, lerpTwo, 0.392);

        if(biome_value > 0.5) {
                return PLAINS;
        }

        return OCEAN; 
}

static world_chunk_t* create_chunk(vec2_t origin_pos, biome_t biome) {
        world_chunk_t* chunk = malloc(sizeof(world_chunk_t));
        if(chunk == NULL){
                return NULL;
        }

        chunk->origin_pos = origin_pos;
        chunk->biome = determine_chunk_biome(origin_pos);

        generate_chunk_tile_data(chunk);

        return chunk;
}




void init() {
        chunks = create_hash_map();
}




