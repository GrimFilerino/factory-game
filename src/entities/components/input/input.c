#include "input.h"
#include "../../../hashmap/hashmap.h"

struct EntityInputs {
        input_t** inputs;
        int current_index;
};

Hashmap* input_action;


/*
void handlePlayerMovment(Player* player) {
        player->velocity.y = 0.0f;
        player->velocity.x = 0.0f;
        
        if(IsKeyDown(KEY_W)) {
                player->velocity.y = -player->speed * GetFrameTime(); 
        } else if(IsKeyDown(KEY_S)){
                player->velocity.y = player->speed * GetFrameTime();
        }

        if(IsKeyDown(KEY_A)) {
                player->velocity.x = - player->speed * GetFrameTime(); 
        } else if(IsKeyDown(KEY_D)){
                player->velocity.x = player->speed * GetFrameTime();
        }


        player->position.y += player->velocity.y;
        player->position.x += player->velocity.x;
}
*/

void bind_input(char* entityId, input_t* input) {
        if(input_action == NULL) {
                input_action = create_hash_map();
        }

        void* data = hash_map_get(input_action, entityId);
        if(data == NULL) {
                return;
        }

        hash_map_add(input_action, input->key, input); 
}

void unbind_input(char* entityId, char* key) {
        hash_map_remove(input_action, key); 
}

void handle_input(entity_t* entity) {
                
}
