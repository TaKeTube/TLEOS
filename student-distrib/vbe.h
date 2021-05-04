/* 
 * Bochs VBE Extensions 
 * Reference: https://wiki.osdev.org/Bochs_VBE_Extensions
 */

#ifndef _VBE_H
#define _VBE_H

#include "types.h"
#include "lib.h"

#define VBE_DISPI_IOPORT_INDEX          0x01CE
#define VBE_DISPI_IOPORT_DATA           0x01CF

#define VBE_DISPI_INDEX_ID              0x0
#define VBE_DISPI_INDEX_XRES            0x1
#define VBE_DISPI_INDEX_YRES            0x2
#define VBE_DISPI_INDEX_BPP             0x3
#define VBE_DISPI_INDEX_ENABLE          0x4
#define VBE_DISPI_INDEX_BANK            0x5
#define VBE_DISPI_INDEX_VIRT_WIDTH      0x6
#define VBE_DISPI_INDEX_VIRT_HEIGHT     0x7
#define VBE_DISPI_INDEX_X_OFFSET        0x8
#define VBE_DISPI_INDEX_Y_OFFSET        0x9

#define VBE_DISPI_BPP_32                0x20

#define VBE_DISPI_DISABLED              0x00
#define VBE_DISPI_ENABLED               0x01

#define VBE_DISPI_INDEX_FB_BASE_HI      0x0B

#define VBE_FB_ADDR                     0xFD000000  /* This address can be seen from qemu info qtree */
#define VBE_FB_BASE_HI_OFFSET           16

#define VBE_DISPI_XRES                  1600
#define VBE_DISPI_YRES                  1200

void copy_fb(void* fb_addr, void* vidmem_addr, int num_longwords);

void bga_reg_write(uint16_t index, uint16_t value);

uint16_t bga_reg_read(uint16_t index);

void bga_set_video_mode(uint16_t w, uint16_t h, uint16_t bpp);

void bga_clear();

#endif
