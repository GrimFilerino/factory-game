#ifndef SCENE_H 
#define SCENE_H

typedef enum scenes {
        MENU,
        WORLD
} scenes_t;

void scene_initialize();
void scene_play();

#endif
