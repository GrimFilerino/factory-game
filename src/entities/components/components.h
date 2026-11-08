#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <stdbool.h>

typedef enum components {
        COMPONENT_TRANSFORM,
        COMPONENT_CAMERA,
        COMPONENT_INPUT,
        COMPONENT_AABB,
} components_t;

bool has_component(char* id, components_t component);

#endif
