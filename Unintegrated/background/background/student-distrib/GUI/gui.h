#ifndef _GUI_H
#define _GUI_H

#include "vbe.h"
#include "graphics.h"

#define SCREEN_X            VBE_DISPI_XRES
#define SCREEN_Y            VBE_DISPI_YRES

#define STATUS_BAR_X        SCREEN_X
#define STATUS_BAR_Y        60
#define STATUS_BAR_SIZE     STATUS_BAR_X * STATUS_BAR_Y


/* color format: 0x00RRGGBB */
#define STATUS_BAR_COLOR        0x00662377
#define STATUS_BAR_MSG_COLOR    0x00000000
#define BACKGROUND_COLOR        0x00FC867D

void gui_init();

void gui_test();

void render_screen();

void render_background(int32_t* fb, int32_t color);

void render_status_bar(int32_t* fb, int32_t color);

void render_window();

void render_cursor();

#endif
