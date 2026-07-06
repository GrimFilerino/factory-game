#ifndef GUI_H 
#define GUI_H

#include "raylib.h"
#include "../math/vector.h"

typedef enum gui_type {
        TEXT_BOX
} gui_type_t;


typedef struct text_box_data {
        char *text;
        Texture2D* texture;
        Font* font;
        float font_size;
        vec2_t pos;
} text_box_data_t;

void init_gui_manager();
void create_gui(gui_type_t type, void* data);
void update_guis();
void delete_guis();

#endif 
