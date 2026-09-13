#include "world-generation.h"
#include "../../../../hashmap/hashmap.h"
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

static void generate_chunk_tile_data(float** perlin_noise, world_chunk_t* chunk) {
        for(int x = 0; x < CHUNK_WIDTH; x++) {
                for(int y = 0; y < CHUNK_HEIGHT; y++) {
                        int noise_x = (int)(chunk->origin_pos.x + x * TILE_SIZE);
                        int noise_y = (int)(chunk->origin_pos.y + y * TILE_SIZE);

                        float tile_noise_value = perlin_noise[noise_x][noise_y];

                        tile_t tile = get_tile_type(tile_noise_value, chunk->biome);
                }
        }
}

static float** get_chunk_perlin_noise(vec2_t offset){
       //generate or get perlin noise idk yet 
}

static world_chunk_t* create_chunk(vec2_t origin_pos, biome_t biome) {
        world_chunk_t* chunk = malloc(sizeof(world_chunk_t));
        if(chunk == NULL){
                return NULL;
        }

        chunk->origin_pos = origin_pos;
        chunk->biome = biome;

        float** perlin_noise = get_chunk_perlin_noise(origin_pos);

        generate_chunk_tile_data(perlin_noise, biome, chunk->tile_data);

        return chunk;
}




void init() {
        chunks = create_hash_map();
}




