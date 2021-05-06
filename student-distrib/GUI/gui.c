#include "gui.h"
#include "bg.h"
#include "text.h"
#include "fastmemcopy.h"

void gui_init()
{
    int i = 0;
    bga_set_video_mode(VBE_DISPI_XRES, VBE_DISPI_YRES, VBE_DISPI_BPP_32);
    for(i = 0; i < WINDOW_NUM; i++){
        windows[i].h = NUM_ROWS*(FONT_HEIGHT<<FONT_MAGNIFICATION);
        windows[i].w = NUM_COLS*(FONT_WIDTH<<FONT_MAGNIFICATION);
    }
    windows[0].x = 100;
    windows[0].y = 400;
    windows[0].term_id = 0;
    windows[1].x = 800;
    windows[1].y = 200;
    windows[1].term_id = 1;
    windows[2].x = 800;
    windows[2].y = 600;
    windows[2].term_id = 2;
}

void gui_render_screen()
{
    int32_t* fb = (int32_t*)FRAME_BUFFER_1_ADDR;
    /* render background */
    gui_render_background(fb, DESKTOP_BG_COLOR);
    /* render status bar */
    gui_render_status_bar(fb, STATUS_BAR_COLOR);
    status_bar_changed = 1;
    /* render window */
    // render_window(fb);
    windows[0].is_changed = 1;
    /* render cursor */
    gui_render_cursor();
    cursor_changed = 0;
    /* copy framebuffer to video memory */
    copy_fb((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, FB_SIZE);
}

void gui_update_screen()
{
    // int32_t* fb = (int32_t*)FRAME_BUFFER_1_ADDR;
    int32_t* fb = (int32_t*)VBE_FB_ADDR;

    /* render status bar */
    if(status_bar_changed){
        // gui_update_status_bar(fb, STATUS_BAR_COLOR);
        // status_bar_changed = 0;
    }
    /* render window */
    if(windows[0].is_changed){
        gui_update_window(fb);
        // windows[0].is_changed = 0;
    }
    /* render cursor */
    if(cursor_changed){
        gui_update_cursor();
        cursor_changed = 0;
    }
}

void gui_render_background(int32_t* fb, int32_t color)
{
    int i;
    int j;
    for(i = 0; i < FB_SIZE; i++)
        fb[i] = color;

    int base_x = 600;
    int base_y = 225;
    int32_t* frame_buffer = (int32_t*)FRAME_BUFFER_1_ADDR;
   
    for(i = 0; i < IMAGE_Y; i++)
    {
        for (j = 0; j < IMAGE_X; j++)
        {
            frame_buffer[(base_y+i)*VBE_DISPI_XRES+(base_x+j)] = image[i*IMAGE_X+j];
        }
    }

    copy_fb((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, FB_SIZE);
    return;
}

void gui_render_status_bar(int32_t* fb, int32_t color)
{
    static int j = 100;
    int i;

    j = (j+1)%STATUS_BAR_X;

    for(i = 0; i < STATUS_BAR_SIZE; i++)
        fb[i] = color;
    // fill_fb(color, (int32_t*)FRAME_BUFFER_1_ADDR, STATUS_BAR_SIZE);

    draw_text(j , STATUS_BAR_Y/2 - FONT_HEIGHT/2, fb, "TOBACCO, LEFT & EYEWASH", STATUS_BAR_MSG_COLOR);

    draw_rect(0, STATUS_BAR_Y, STATUS_BAR_X, 3, 0x00E3E3E3, fb);

    return;
}

// void render_window(int pos_x, int pos_y, int width, int height, int margin_width, int32_t color_background, int32_t color_margin, int32_t *fb)
// {
// }

void gui_render_window(int32_t* fb)
{
    int term_id;
    for(term_id = 0; term_id < TERMINAL_NUM; term_id++){
        if(terminals[term_id].is_running){
            // gui_render_terminal(term_id, term_id, fb);
            // FIXME
            // render_window_margin(term_id, fb);
        }
    }
}

void gui_render_window_margin(int32_t win_id, int32_t* fb)
{
    // FIXME
    int32_t pos_x = windows[win_id].x;
    int32_t pos_y = windows[win_id].y;
    int32_t height = windows[win_id].h;
    int32_t width = windows[win_id].w;
    int32_t margin_width = 10;
    draw_rect(pos_x-margin_width, pos_y-margin_width, width+(margin_width<<2), margin_width, WINDOW_MARGIN_COLOR, fb);
    draw_rect(pos_x-margin_width, pos_y+height, width+(margin_width<<2), margin_width, WINDOW_MARGIN_COLOR, fb);
    draw_rect(pos_x-margin_width, pos_y, margin_width, height, WINDOW_MARGIN_COLOR, fb);
    draw_rect(pos_x+width+margin_width, pos_y, margin_width, height, WINDOW_MARGIN_COLOR, fb);
}

void gui_render_terminal(int32_t win_id, int32_t term_id, int32_t* fb)
{
    int32_t i, j, x, y;
    int32_t char_pos;
    int32_t global_offset, local_offset;
    // FIXME
    // uint8_t* term_vidbuf = terminals[term_id].vid_buf;
    uint8_t* term_vidbuf = (uint8_t*)VIDEO;
    unsigned char *bitmap;

    global_offset = windows[win_id].x + windows[win_id].y * SCREEN_X;

    for(j = 0; j < NUM_ROWS; j++){
        for(i = 0; i < NUM_COLS; i++){
            char_pos = (i<<1) + (j<<1) * NUM_COLS;
            bitmap = font_data[(int)term_vidbuf[char_pos]];
            local_offset = 0;
            /* loop that character in row major way */
            for (y = 0; y < (FONT_HEIGHT << FONT_MAGNIFICATION); y++){
                /* mask value init to 0x80 = 0b10000000, which will be shifted to right bit by bit */
                unsigned char mask = 0x80;
                /* loop every pixel in the current row */
                for (x = 0; x < (FONT_WIDTH << FONT_MAGNIFICATION); x++){
                    /* mask to check the corresponding bit and set the pixel to input color */
                    if (mask & bitmap[j >> FONT_MAGNIFICATION])
                        fb[global_offset + local_offset] = TERMINAL_TEXT_COLOR;
                    // else
                        // fb[global_offset + local_offset] = TERMINAL_BG_COLOR;
                    /* right shift mask by a bit*/
                    mask >>= 1;
                    local_offset++;
                }
                local_offset += FONT_WIDTH << FONT_MAGNIFICATION;
            }
            global_offset ++;
        }
        global_offset += SCREEN_X;
    }
    return;
}

void gui_render_cursor()
{
    return;
}

void gui_update_background(int32_t* fb, int32_t color)
{
    return;
}

void gui_update_status_bar(int32_t* fb, int32_t color)
{
    static int j = 0;
    int i;
    j = (j+1)%STATUS_BAR_X;
    for(i = 0; i < STATUS_BAR_SIZE; i++)
        fb[i] = color;
    draw_text(j , STATUS_BAR_Y/2 - FONT_HEIGHT/2, fb, "This is status bar", STATUS_BAR_MSG_COLOR);
    // copy_fb((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, STATUS_BAR_SIZE);
    // fast_memcpy((int32_t*)FRAME_BUFFER_1_ADDR, (int32_t*)VBE_FB_ADDR, STATUS_BAR_SIZE * 4);
    return;
}

void gui_update_window(int32_t* fb)
{
    int term_id;
    for(term_id = 0; term_id < TERMINAL_NUM; term_id++){
        if(terminals[term_id].is_running && windows[term_id].is_changed){
            gui_update_terminal(term_id, term_id, fb);
            // FIXME
            // render_window_margin(term_id, fb);
        }
    }
}

void gui_update_terminal(int32_t win_id, int32_t term_id, int32_t* fb)
{
    int32_t i, j, x, y;
    int32_t char_pos;
    int32_t global_offset, local_offset;
    // FIXME
    uint8_t* term_vidbuf = terminals[term_id].vid_buf;
    // uint8_t* term_vidbuf = (uint8_t*)VIDEO;
    unsigned char *bitmap;

    global_offset = windows[win_id].x + windows[win_id].y * SCREEN_X;

    for(j = 0; j < NUM_ROWS; j++){
        for(i = 0; i < NUM_COLS; i++){
            char_pos = (i<<1) + j * (NUM_COLS<<1);
            bitmap = font_data[(int)term_vidbuf[char_pos]];
            local_offset = 0;
            /* loop that character in row major way */
            for (y = 0; y < (FONT_HEIGHT << FONT_MAGNIFICATION); y++){
                /* mask value init to 0x80 = 0b10000000, which will be shifted to right bit by bit */
                unsigned char mask = 0x80;      
                /* loop every pixel in the current row */
                for (x = 0; x < (FONT_WIDTH << FONT_MAGNIFICATION); x++){
                    /* mask to check the corresponding bit and set the pixel to input color */
                    local_offset = (VBE_DISPI_XRES * y) + x;
                    if (mask & bitmap[y >> FONT_MAGNIFICATION])
                        fb[global_offset + local_offset] = TERMINAL_TEXT_COLOR;
                    else
                        fb[global_offset + local_offset] = TERMINAL_BG_COLOR;
                    /* right shift mask by a bit*/
                    mask >>= 1;
                }
            }
            global_offset += (FONT_WIDTH << FONT_MAGNIFICATION);
        }
        global_offset += (SCREEN_X * (FONT_HEIGHT << FONT_MAGNIFICATION)) - (FONT_WIDTH << FONT_MAGNIFICATION) * NUM_COLS;
    }
}

void gui_update_cursor()
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