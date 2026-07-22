#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"
#include "rcamera.h"

int main() {
        const int screenWidth = 800;
        const int screenHeight = 450;
        InitAudioDevice();

        InitWindow(screenWidth, screenHeight, "Factory Game");

        game_init();

        CloseWindow(); 
        return 0;
}

