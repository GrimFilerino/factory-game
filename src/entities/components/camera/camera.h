#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>


typedef struct tracing_camera {
        Camera2D* camera;
        char* entity_id;
} tracing_camera_t;

void initialize_camera(Camera2D* camera);
void switch_entity_to_trace(char* entity_id);
void trace_entity_with_camera();

#endif
