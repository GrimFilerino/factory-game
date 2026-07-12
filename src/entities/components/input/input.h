#ifndef INPUT_H
#define INPUT_H

#include "../../entity.h"
#define MAX_INPUTS 4

typedef enum actions {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGTH,
} actions_t;

typedef struct input {
        char* key;
        actions_t action;
} input_t;

void bind_input(char* entityId, input_t input);
void unbind_input(char* entityId, char* key);

void check_input();
void handle_input(entity_t* entity);


#endif

