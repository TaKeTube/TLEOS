#include "gui.h"
#include "text.h"

void gui_init()
{
    bga_set_video_mode(VBE_DISPI_XRES, VBE_DISPI_YRES, VBE_DISPI_BPP_32);
}

void render_screen()
{
    int32_t* fb = (int32_t*)FRAME_BUFFER_1_ADDR;
    /* render background */
    render_background(fb, BACKGROUND_COLOR);
    /* render status bar */
    render_status_bar(fb, STATUS_BAR_COLOR);
    /* render window */
    render_window();
    /* render cursor */
    render_cursor();
    copy_fb((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, FB_SIZE);
}

void render_background(int32_t* fb, int32_t color)
{
    int i;
    for(i = 0; i < FB_SIZE; i++)
        fb[i] = color;
    return;
}

void render_status_bar(int32_t* fb, int32_t color)
{
    static int j = 0;
    int i;

    j = (j+1)%STATUS_BAR_X;

    for(i = 0; i < STATUS_BAR_SIZE; i++)
        fb[i] = color;

    draw_text(j , STATUS_BAR_Y/2 - FONT_HEIGHT/2, fb, "This is status bar", STATUS_BAR_MSG_COLOR);

    return;
}

void render_window()
{
    return;
}

void render_cursor()
{
    return;
}

void gui_test(){
    int i;
    int32_t* frame_buffer = (int32_t*)FRAME_BUFFER_1_ADDR;
    int32_t color = 0x00FF0000;
    int32_t text_color = 0x0000FF00;

    for(i = 0; i < VBE_DISPI_XRES * 10; i++)
        frame_buffer[i] = 0x00FF8833;

    draw_rect(100, 100, 500, 700, color, frame_buffer);

    draw_text(100, 100, frame_buffer, "TLEOS", text_color);

    copy_fb((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, FB_SIZE);
}
