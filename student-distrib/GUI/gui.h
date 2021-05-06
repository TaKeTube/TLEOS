#ifndef _GUI_H
#define _GUI_H

#include "vbe.h"
#include "graphics.h"
#include "../terminal.h"

#define STATUS_BAR_X        SCREEN_X
#define STATUS_BAR_Y        50
#define STATUS_BAR_SIZE     STATUS_BAR_X * STATUS_BAR_Y

/* color format: 0x00RRGGBB */
// #define STATUS_BAR_COLOR         0x00662377
#define STATUS_BAR_COLOR         0x00566687
#define STATUS_BAR_MSG_COLOR     0x00E3E3E3
#define DESKTOP_BG_COLOR         0x00021830
#define WINDOW_MARGIN_COLOR      0x00FFFFFF
#define TERMINAL_BG_COLOR        0x00021830
#define TERMINAL_TEXT_COLOR      0x00FFFFFF

#define WINDOW_NUM          TERMINAL_NUM

typedef struct gui_window_t {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
    uint32_t win_id;
    uint32_t term_id;
    uint8_t is_focused;
    uint8_t is_changed;
    uint8_t is_scrolled;
} gui_window_t;

gui_window_t windows[TERMINAL_NUM];

int status_bar_changed;
int cursor_changed;

void gui_init();

void gui_test();

void gui_render_screen();

void gui_render_background(int32_t* fb, int32_t color);

void gui_render_status_bar(int32_t* fb, int32_t color);

void gui_render_window();

void gui_render_window_margin(int32_t win_id, int32_t* fb);

void gui_render_terminal(int32_t win_id, int32_t term_id, int32_t* fb);

void gui_render_cursor();

void gui_update_screen();

void gui_update_background(int32_t* fb, int32_t color);

void gui_update_status_bar(int32_t* fb, int32_t color);

void gui_update_window(int32_t* fb);

void gui_update_terminal(int32_t win_id, int32_t term_id, int32_t* fb);

void gui_update_cursor();

#endif
