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

void bind_input(char* entityId, input_t input) {
        if(input_action == NULL) {
                input_action = create_hash_map();
        }

        void* data = hash_map_get(input_action, entityId);
        if(data == NULL) {
                struct EntityInputs new_data = {0};
                new_data.current_index = 0;
                new_data.inputs = calloc(MAX_INPUTS, sizeof(input_t));

                input_t* new_input = malloc(sizeof(input_t));
                new_input->key = input.key;
                new_input->action = input.action;

                new_data.inputs[new_data.current_index] = new_input;
                return;
        }

        
        struct EntityInputs* input_data = (struct EntityInputs *)data;
        input_data->current_index++;


        input_t* new_input = malloc(sizeof(input_t));
        new_input->key = input.key;
        new_input->action = input.action;

        input_data->inputs[input_data->current_index] = new_input;

}
void unbind_input(char* entityId, char* key);

void check_input();
void handle_input(entity_t* entity);
