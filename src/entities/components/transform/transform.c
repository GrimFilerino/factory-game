#include "transform.h"

void applyVelocityToPosition(transform_t* transform){
        *transform->position = add_vector(*transform->position, *transform->velocity);
        set_vector_to_constant(transform->velocity, 0);
}

