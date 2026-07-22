#ifndef INPUT_H
#define INPUT_H

#include "../transform/transform.h"
#include "../../entity.h"

#define ACTION_SIZE 5

typedef enum actions {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGTH,
        ATTACK
} actions_t;

typedef struct input {
        char* key;
        actions_t action;
        int key_code;
} input_t;

void bind_input(actions_t action, int key_code);
void unbind_input(char* action);
void handle_input(char* entity_id);

const char* get_hash_map_key(actions_t action);

#endif

