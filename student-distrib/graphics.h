#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "vbe.h"

#define FB_PAGE_SIZE                0x800000
#define FB_BASE_ADDR                0x2000000
#define FRAME_BUFFER_1_ADDR         (FB_BASE_ADDR + FB_PAGE_SIZE)
#define FRAME_BUFFER_2_ADDR         (FB_BASE_ADDR + FB_PAGE_SIZE)

#endif
