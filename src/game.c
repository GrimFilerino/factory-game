#include "game.h"
#include "scenes/scene.h"
#include <raylib.h>


static void game_play() {
        while (!WindowShouldClose()) {
                scene_play();
        }
}


//Load save files, settings and other things
void game_init() {
        scene_initialize();
        game_play();
}
