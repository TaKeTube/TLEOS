#include "gui.h"

void gui_init()
{
    bga_set_video_mode(VBE_DISPI_XRES, VBE_DISPI_YRES, VBE_DISPI_BPP_32);
}

void gui_test(){
    int i;
    int32_t* frame_buffer = (int32_t*)FRAME_BUFFER_1_ADDR;
    color_t color = {0x00, 0xFF, 0x00, 0x00};
    color_t text_color = {0x00, 0x00, 0xFF, 0x00};

    for(i = 0; i < VBE_DISPI_XRES * 10; i++)
        frame_buffer[i] = 0x00FF8833;

    draw_rect(100, 100, 500, 700, color, (color_t*)frame_buffer);

    text2image(100, 100, (color_t*)frame_buffer, "xt chi da bian", text_color);

    copy_fb((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, VBE_DISPI_XRES*VBE_DISPI_YRES);
}
