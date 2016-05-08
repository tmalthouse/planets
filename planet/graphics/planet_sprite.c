//
//  planet_sprite.c
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "planet_sprite.h"
#include <stdlib.h>
#include "window.h"

PSprite new_psprite(CBody *body, Texture *tex)
{
    PSprite planet;
    planet.rootbody = body;
    planet.texture = tex;
    planet.width = 5;
    planet.height = 5;
    planet.screenpos = screencoord(body->pos);
    planet.screenvel = screencoord(body->vel);
    return planet;
}

void psprite_update(PSprite *planet) {
    planet->screenpos = screencoord(planet->rootbody->pos);
}

void psprite_render(PSprite *planet, SDL_Renderer *renderer) {
    render_texture(planet->texture, planet->screenpos, renderer, RENDER_DEFAULT_ARGS);
}
