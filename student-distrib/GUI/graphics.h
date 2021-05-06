#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "vbe.h"
#include "text.h"

#define SCREEN_X            VBE_DISPI_XRES
#define SCREEN_Y            VBE_DISPI_YRES

#define FB_PAGE_SIZE                0x800000
#define FB_SIZE                     VBE_DISPI_XRES * VBE_DISPI_YRES
#define FB_BASE_ADDR                0x2000000
#define FRAME_BUFFER_1_ADDR         (FB_BASE_ADDR)
#define FRAME_BUFFER_2_ADDR         (FB_BASE_ADDR + FB_PAGE_SIZE)

typedef struct color {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
} color_t;

inline void draw_pixel(int pos_x, int pos_y, int32_t color, int32_t *fb);
void draw_rect(int upper_left_x, int upper_left_y, int width, int height, int32_t color, int32_t *fb);
void draw_text(int pos_x, int pos_y, int32_t *fb, char *text, int32_t text_color);

#endif
