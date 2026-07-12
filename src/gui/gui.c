#include "gui.h"
#include <stdlib.h>
#include "../hashmap/hashmap.h"

char** gui_keys;
unsigned char gui_index = 0;

Hashmap* guis;

typedef struct gui_base {
        gui_type_t type;
} gui_base_t;

typedef struct gui_text_box {
        char* id;
        gui_type_t type;
        char *text;
        Texture2D* texture;
        Font* font;
        float font_size;
        vec2_t text_pos;
        vec2_t pos;
        vec2_t size;
        float life_time;
        float current_life_time;
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

static void draw_gui_text_box(gui_text_box_t* box) {
        NPatchInfo patch = {.source = {0, 0, box->texture->width, box->texture->height},
                .left = 16,
                .right = 16,
                .top = 16,
                .bottom = 16,
                .layout = NPATCH_NINE_PATCH
        };

        Vector2 size = MeasureTextEx(*box->font, box->text, box->font_size, 1.0f);
        Rectangle dest = { box->pos.x, box->pos.y, size.x * 1.25f, box->texture->height };
        DrawTextureNPatch(*box->texture, patch, dest, (Vector2){0, 0}, 0.0f, WHITE);
        DrawTextEx(*box->font, box->text, (Vector2){box->pos.x + box->text_pos.x, box->pos.y + box->text_pos.y}, box->font_size, 1.0f, WHITE);
}

static gui_text_box_t* create_gui_text_box(char *text, float font_size, vec2_t pos, Font* font, Texture2D* texture) {
        gui_text_box_t *box = malloc(sizeof(gui_text_box_t));
        if (!box) {
                return NULL;
        }

        box->text = text;
        box->font_size = font_size;
        box->font = font;
        box->pos = pos;
        box->text_pos = (vec2_t){.x = 16.0, .y = 16.0};
        box->texture = texture;

        return box;
}


static void delete_gui_text_box(gui_text_box_t* box) {
        free(box);
        box = NULL;
}



void init_gui_manager(){
        guis = create_hash_map();
        gui_keys = malloc(sizeof(char*) * 20);
}

void create_gui(gui_type_t type, void* data){
        text_box_data_t* box;
        switch (type) {
                case TEXT_BOX:
                        box = (text_box_data_t*)data;
                        gui_text_box_t* new_box = create_gui_text_box(box->text, box->font_size, box->pos, box->font, box->texture);
                        hash_map_add(guis, new_box->id, (void*)new_box);
                        gui_keys[gui_index] = new_box->id;
                        gui_index++;
                break;
        }
}
void update_guis() {
        for(unsigned short i = 0; i < gui_index; i++) {
                char* key = gui_keys[i];
                void* data = hash_map_get(guis, key);
                gui_base_t* gui_base = (gui_base_t*)data;
                
                if(gui_base->type == TEXT_BOX) {
                        gui_text_box_t* box = (gui_text_box_t*)data;
                        draw_gui_text_box(box);
                }
        }
}
void delete_guis(){
}

