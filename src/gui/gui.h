#ifndef GUI_H 
#define GUI_H

#include "raylib.h"
#include "../math/vector.h"

typedef struct gui_text_box {
        char *text;
        Texture2D* texture;
        Font* font;
        float font_size;
        vec2_t text_pos;
        vec2_t pos;
        vec2_t size;
} gui_text_box_t;


/*
typedef struct gui_item_text_box {
        char *text;
        char* item_id;
        Texture2D texture;
        Font font;
        float font_size;
        vec2_t text_pos;
        vec2_t pos;
        vec2_t size;
} gui_item_text_box_t;
*/

gui_text_box_t* create_gui_text_box(char *text, float font_size, vec2_t pos, Font* font, Texture2D* texture);
void draw_gui_text_box(gui_text_box_t* box);
void delete_gui_text_box(gui_text_box_t* box);

#endif 
