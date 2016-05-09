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
#include <SDL2/SDL.h>
#include "texture.h"
#include "psprite.h"
#include "../coord.h"
#include "../cbody.h"
#include "../darray_types.h"

PSprite new_psprite();
void psprite_update(PSprite *planet);
void psprite_render(PSprite *planet, SDL_Renderer *renderer);
void render_labels (Darray_PSprite *bodies, Coordinate mousepos, SDL_Renderer *renderer);

#endif /* planet_sprite_h */
