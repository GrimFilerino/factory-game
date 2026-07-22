#include "game.h"
#include "scenes/scene.h"
#include <raylib.h>


void game() {
        scene_initialize(); 
        while (!WindowShouldClose()) {
                scene_play();
        }
}
