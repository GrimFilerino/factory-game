#include "scene.h"
#include "worlds/overworld/overworld.h"
#include <raylib.h>

scenes_t current_scene;


static void deinitialize_scene() {
        switch (current_scene) {
                case MENU:
                break;

                case WORLD:
                        world_deinitialize();
                break;

                default:
                break;
        }
}

static void initalize_scene() {
        switch (current_scene) {
                case MENU:
                break;

                case WORLD:
                        world_initialize();
                break;
        }
}

void switch_scene(scenes_t scene) {
        deinitialize_scene();
        current_scene = scene;
        initalize_scene();
}

void scene_initialize() {
        SetTargetFPS(60);
        switch_scene(WORLD);
}

void scene_play() {
        switch (current_scene) {
                case MENU:
                break;

                case WORLD:
                        world_play();
                break;
        }
}



