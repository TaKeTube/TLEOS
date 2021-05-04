#include "gui.h"

void gui_init()
{
    bga_set_video_mode(VBE_DISPI_XRES, VBE_DISPI_YRES, VBE_DISPI_BPP_32);
}

void gui_test(){
    int i;
    int32_t* frame_buffer = (int32_t*)FRAME_BUFFER_1_ADDR;

    for(i = 0; i < VBE_DISPI_XRES * 10; i++)
        frame_buffer[i] = 0x00FF8833;

    copy_fb((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, VBE_DISPI_XRES*VBE_DISPI_YRES);
}
