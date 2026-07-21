#include "camera.h"
#include "../transform/transform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tracing_camera_t *camera_tracer;

void initialize_camera(Camera2D *camera) {
        camera_tracer = malloc(sizeof(tracing_camera_t));
        if (camera_tracer == NULL) {
                return;
        }

        camera_tracer->camera = camera;
        camera_tracer->entity_id = malloc(37);
        camera_tracer->entity_id[0] = '\0'; 
}

void switch_entity_to_trace(char *entity_id) {
        strcpy(camera_tracer->entity_id, entity_id);
}

void trace_entity_with_camera() {
        //this does not work...
        transform_t* transform = get_transform_component(camera_tracer->entity_id);

        if(!transform) {
                printf("nooooo \n");
                return;
        }

        Camera2D *camera = camera_tracer->camera;
        if (camera) {
                camera->target = (Vector2){.x = transform->position->x, .y = transform->position->y};
                camera->rotation = 0.0;
        }
}

