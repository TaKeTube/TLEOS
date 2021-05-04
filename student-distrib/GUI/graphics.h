#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "vbe.h"
#include "text.h"

#define FB_PAGE_SIZE                0x800000
#define FB_BASE_ADDR                0x2000000
#define FRAME_BUFFER_1_ADDR         (FB_BASE_ADDR + FB_PAGE_SIZE)
#define FRAME_BUFFER_2_ADDR         (FB_BASE_ADDR + FB_PAGE_SIZE)

typedef struct color {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
} color_t;

/* The default VGA text mode font is 8x16 pixels. */
#define FONT_WIDTH   8
#define FONT_HEIGHT  16

void draw_pixel(int pos_x, int pos_y, color_t color, color_t *framebuffer);
void draw_rect(int left_upper_x, int left_upper_y, int width, int height, color_t color, color_t *framebuffer);
void text2image(int pos_x, int pos_y, color_t *framebuffer, char *text, color_t text_color);

#endif
