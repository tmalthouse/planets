//
//  texture.h
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef texture_h
#define texture_h

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "../coord.h"

#define RENDER_DEFAULT_ARGS = NULL, 0.0, NULL, SDL_FLIP_NONE

typedef struct {
    SDL_Texture *texture;
    int height;
    int width;
} Texture;

Texture *load_texture (char *path);
void free_texture(Texture *t);
void texture_set_color(Texture *t, uint8_t r, uint8_t g, uint8_t b);
void texture_set_blend_mode(Texture *t, SDL_BlendMode blend);
void texture_set_alpha(Texture *t, uint8_t alpha);
void render_texture(Texture *t, coordinate pos, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip);


#endif /* texture_h */
