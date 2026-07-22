#include "sound.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Sound* sounds[MAX_SOUNDS];


const char* SOUNDS_NAME[MAX_SOUNDS] = {
        "item.wav"
};


static char* get_sound_path(const char* fileName) {
        char* path = malloc(1024);
        snprintf(path, 1024, "%sassets/sounds/%s", GetApplicationDirectory(), fileName); 
        return path;
}

void initialize_sounds() {
        for(int i = 0; i < MAX_SOUNDS; i++) {
               sounds[i] = malloc(sizeof(Sound));
               Sound sound = LoadSound(get_sound_path(SOUNDS_NAME[i])); 
               sounds[i]->stream = sound.stream;
               sounds[i]->frameCount = sound.frameCount;
        }
}


void play_sound(sounds_t type) {
        SetMasterVolume(100);
        Sound* sound = sounds[type];

        if(!IsSoundPlaying(*sound)) {
                PlaySound(*sound);
        }
}
