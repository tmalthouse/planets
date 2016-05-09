//
//  psprite.h
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef psprite_h
#define psprite_h
#include "texture.h"
#include "../cbody.h"

typedef struct {
    CBody *rootbody;
    Texture *texture;
    Texture *label;
    int width;
    int height;
    Coordinate screenpos;
    Vector2d screenvel;
} PSprite;

#endif /* psprite_h */
