//
//  planet_sprite.h
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef planet_sprite_h
#define planet_sprite_h

#include <stdio.h>
#include "texture.h"
#include "../coord.h"
#include "../cbody.h"

typedef struct {
    cbody *rootbody;
    Texture *texture;
    int width;
    int height;
    coordinate screenpos;
    vector2d screenvel;
} PSprite;

PSprite *new_psprite();
void psprite_move(PSprite *planet);
void psprite_render(PSprite *planet);
void free_psprite(PSprite *planet);


#endif /* planet_sprite_h */
