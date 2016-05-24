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
    COLOR_WHITE = 0xFFFFFFFF,
    COLOR_BLACK = 0xFF000000,
    COLOR_GRAY  = 0xFF777777,
    COLOR_RED   = 0xFFC72923,
    COLOR_ORANGE= 0xFFC3781C,
    COLOR_YELLOW= 0xFFEBF209,
    COLOR_GREEN = 0xFF2F7013,
    COLOR_BLUE  = 0xFF313b8F,
    COLOR_TEAL  = 0xFF008080
} BasicColor;

Color hex_color(uint32_t);
uint32_t color_hex(Color c);

#endif /* color_h */
