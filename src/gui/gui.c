#include "gui.h"
#include <stdlib.h>

void draw_gui_text_box(gui_text_box_t* box) {
        NPatchInfo patch = {.source = {0, 0, box->texture.width, box->texture.height},
                .left = 16,
                .right = 16,
                .top = 16,
                .bottom = 16,
                .layout = NPATCH_NINE_PATCH
        };

        Vector2 size = MeasureTextEx(*box->font, box->text, box->font_size, 1.0f);
        Rectangle dest = { box->pos.x, box->pos.y, size.x * 1.25f, box->texture.height };
        DrawTextureNPatch(*box->texture, patch, dest, (Vector2){0, 0}, 0.0f, WHITE);
        DrawTextEx(*box->font, box->text, (Vector2){box->pos.x + box->text_pos.x, box->pos.y + box->text_pos.y}, box->font_size, 1.0f, WHITE);
}

gui_text_box_t* create_gui_text_box(char *text, float font_size, vec2_t pos, Font* font, Texture2D* texture) {
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


void delete_gui_text_box(gui_text_box_t* box) {
        free(box);
        box = NULL;
}

