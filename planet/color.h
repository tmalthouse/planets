//
//  color.h
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef color_h
#define color_h

#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;



typedef enum {
    COLOR_WHITE = 0xFFFFFF00,
    COLOR_BLACK = 0x00000000,
    COLOR_GRAY  = 0x77777700,
    COLOR_RED   = 0xC7292300,
    COLOR_ORANGE= 0xC3781C00,
    COLOR_YELLOW= 0xEBF20900,
    COLOR_GREEN = 0x2F701300,
    COLOR_BLUE  = 0x313b8F00,
    COLOR_TEAL  = 0x00808000
} SimpleColor;

Color hex_color(uint32_t);
uint32_t color_hex(Color c);

#endif /* color_h */
