#ifndef SOUND_H
#define SOUND_H

#define MAX_SOUNDS 1

typedef enum sounds {
        TEST
} sounds_t;

typedef struct sound {
       char* path;
} sound_t;

void initialize_sounds();
void play_sound(sounds_t type);

#endif
