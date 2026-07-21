#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include "entities/components/camera/camera.h"
#include "entities/entity.h"
#include "gui/gui.h"
#include "raylib.h"
#include "rcamera.h"
#include "entities/entity_manager.h"

int main() {
        const int screenWidth = 800;
        const int screenHeight = 450;
        InitAudioDevice();

        InitWindow(screenWidth, screenHeight, "Factory Game");

        Camera2D* camera = malloc(sizeof(Camera2D));
        
        if(!camera) {
                return 1;
        }

        camera->zoom = 1.0f;
        camera->offset = (Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 };

        initialize_camera(camera);

        init_gui_manager();

        initialize_entity_manager();

        create_entity(PLAYER);
        create_entity(WALL);

        SetTargetFPS(60); 

        while (!WindowShouldClose()) {
                destroy_entities();
                delete_guis();

                BeginDrawing();

                ClearBackground((Color){100, 149, 237, 1.0});

                BeginMode2D(*camera);

                update_entities();
                draw_entities();

                EndMode2D();
                update_guis();

                EndDrawing();

        }

        CloseWindow(); 
        return 0;
}

