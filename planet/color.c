//
//  color.c
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "color.h"
#include "debug.h"


//For both these functions, we treat the hex value (a 32-bit uint) like an array of 4 8-bit values--a, b, g, r in that order.
Color hex_color(uint32_t hex)
{
    //We're assuming intel procs here--little endian.
    Color result;
    uint8_t *hex_ptr = (uint8_t*)&hex;
    dprintf("%x\n", hex);
    result.r = hex_ptr[3];
    result.g = hex_ptr[2];
    result.b = hex_ptr[1];
    return result;
}

uint32_t color_hex(Color c)
{
    uint32_t hex = 0;
    uint8_t *hex_ptr = (uint8_t*)&hex;
    hex_ptr[1] = c.b;
    hex_ptr[2] = c.g;
    hex_ptr[3] = c.r;
    return hex;
}