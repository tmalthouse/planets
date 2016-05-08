//
//  color.c
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "color.h"
#include "debug.h"

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
    return (c.r<<6)+(c.g<<4)+(c.b<<2);
}