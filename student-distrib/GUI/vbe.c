/* 
 * Bochs VBE Extensions 
 * Reference: https://wiki.osdev.org/Bochs_VBE_Extensions
 */
#include "vbe.h"

inline void copy_fb(void* fb_addr, void* vidmem_addr, int num_longwords) {
    asm volatile ("                                             \n\
        cld                                                     \n\
        rep movsl    /* copy ECX bytes from M[ESI] to M[EDI] */ \n\
        "
    : /* no outputs */
    : "S"(fb_addr), "D"(vidmem_addr), "c"(num_longwords)
    : "eax", "memory"
    );
}

// inline void fill_fb(int32_t color, void* vidmem_addr, int num_longwords) {
//     asm volatile ("                                             \n\
//         movl %0, %%eax                                          \n\
//         cld                                                     \n\
//         rep stosl      /* copy ECX bytes from %eax to M[EDI] */ \n\
//         "
//     : /* no outputs */
//     : "r"(color), "S"(0), "D"(vidmem_addr), "c"(num_longwords)
//     : "eax", "memory"
//     );
// }

void copy_block(int32_t* fb_addr, int32_t* vidmem_addr, int offset, int w, int h){
    int i;
    int j;
    for(i = 0, j = 0; i < h; i++, j+=w)
        copy_fb(fb_addr + offset + j, vidmem_addr, w);
}

void bga_reg_write(uint16_t index, uint16_t data)
{
    outw(index, VBE_DISPI_IOPORT_INDEX);
    outw(data, VBE_DISPI_IOPORT_DATA);
}

uint16_t bga_reg_read(uint16_t index)
{
    outw(VBE_DISPI_IOPORT_INDEX, index);
    return inw(VBE_DISPI_IOPORT_DATA);
}

void bga_set_video_mode(uint16_t w, uint16_t h, uint16_t bpp)
{
    bga_reg_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    bga_reg_write(VBE_DISPI_INDEX_XRES, w);
    bga_reg_write(VBE_DISPI_INDEX_YRES, h);
    bga_reg_write(VBE_DISPI_INDEX_BPP, bpp);
    bga_reg_write(VBE_DISPI_INDEX_FB_BASE_HI, VBE_FB_ADDR >> VBE_FB_BASE_HI_OFFSET);
    bga_reg_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED);
}

void bga_clear() {
    bga_reg_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
}
