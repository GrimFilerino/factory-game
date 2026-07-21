#include "input.h"
#include "../../../hashmap/hashmap.h"
#include <math.h>
#include <string.h>
#include <raylib.h>

struct EntityInputs {
        input_t** inputs;
        int current_index;
};

Hashmap* input_action;

const char *action_names[ACTION_SIZE] = {
    "MOVE_UP",
    "MOVE_DOWN",
    "MOVE_LEFT",
    "MOVE_RIGHT"
};


const char* get_hash_map_key(actions_t action) {
        return action_names[action];
}

void bind_input(actions_t action, int key_code) {
        if(input_action == NULL) {
                input_action = create_hash_map();
        }

        input_t* new_input = malloc(sizeof(input_t));
        if(new_input == NULL) {
                return;
        }

        char* action_key = strdup(get_hash_map_key(action));
        new_input->key = strdup(GetKeyName(key_code));
        new_input->action = action;
        new_input->key_code = key_code;

        void* data = hash_map_get(input_action, action_key);
        if(data != NULL) {
                unbind_input(action_key); 
        }

        hash_map_add(input_action, action_key, new_input); 
}

//action is the action_t but as a key 
void unbind_input(char* action) {
        hash_map_remove(input_action, action); 
}

void handle_input(char* entity_id) {
        transform_t* transform = get_transform_component(entity_id);
        float dt = GetFrameTime();

        for(int i = 0; i < ACTION_SIZE; i++){
                char* action = strdup(action_names[i]);
                
                input_t* input = hash_map_get(input_action, action);

                if(IsKeyDown(input->key_code)){
                        switch(input->action) {
                                case MOVE_UP:
                                        transform->velocity->y += -transform->movement_speed * dt; 
                                break;

                                case MOVE_DOWN:
                                        transform->velocity->y += transform->movement_speed * dt;
                                break;

                                case MOVE_LEFT:
                                        transform->velocity->x += -transform->movement_speed * dt; 
                                break;

                                case MOVE_RIGTH:
                                        transform->velocity->x += transform->movement_speed * dt;
                                break;

                        }
                }
               
                free(action);
        }        
       
        apply_uniformed_velocity(entity_id);
}
