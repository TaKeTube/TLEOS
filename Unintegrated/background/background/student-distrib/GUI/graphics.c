#include "graphics.h"

inline void draw_pixel(int pos_x, int pos_y, int32_t color, int32_t *fb)
{
    if (fb == NULL || pos_x < 0 || pos_y < 0 || pos_x >= VBE_DISPI_XRES || pos_y >= VBE_DISPI_YRES)
        return;
    fb[pos_y * VBE_DISPI_XRES + pos_x] = color;
}

void draw_rect(int upper_left_x, int upper_left_y, int width, int height, int32_t color, int32_t *fb)
{
    int i, j;

    if(fb == NULL)
        return;

    for (i = 0; i < width; i++)
        for (j = 0; j < height; j++)
            draw_pixel(upper_left_x+i, upper_left_y+j, color, fb);
}

void draw_text(int pos_x, int pos_y, int32_t *fb, char *text, int32_t text_color)
{
    int i, j, k;                                    // loop indices
    int global_offset, local_offset;
    int text_len;

    if(fb == NULL || text == NULL)
        return;

    text_len = strlen(text);

    global_offset = pos_y * VBE_DISPI_XRES + pos_x;
    /* loop over each character in the string */
    for (i = 0; i < text_len; i++)
    {
        unsigned char *bitmap = font_data[(int)text[i]];   // read that character's info from font_data
        /* loop that character in row major way */
        for (j = 0; j < FONT_HEIGHT * FONT_MAGNIFICATION; j++)
        {
            /* mask value init to 0x80 = 0b10000000, which will be shifted to right bit by bit */
            unsigned char mask = 0x80;      
            /* loop every pixel in the current row */
            for (k = 0; k < FONT_WIDTH * FONT_MAGNIFICATION; k++)
            {
                /* mask to check the corresponding bit and set the pixel to input color */
                if (mask & bitmap[j / FONT_MAGNIFICATION])
                {
                    local_offset = (FONT_WIDTH * i) + (VBE_DISPI_XRES * j) + k;
                    fb[global_offset + local_offset] = text_color;
                }
                /* right shift mask by a bit*/
                mask >>= 1;
            }
        }
    }
}
