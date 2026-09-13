#include "raylib.h"
#include "src/game.h"

int main() {
        const int screenWidth = 800;
        const int screenHeight = 450;

        InitAudioDevice();

        InitWindow(screenWidth, screenHeight, "Factory Game");

        //game loop in here
        game_init();

        CloseWindow(); 
        return 0;
}

