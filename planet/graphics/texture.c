//
//  texture.c
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "texture.h"

Texture *load_texture(char *path, SDL_Renderer *renderer)
{
    Texture *tex = calloc(sizeof(Texture), 1);
    
    SDL_Texture *new_text = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    
    if (loaded_surface == NULL) {
        fprintf(stderr, "Can't load texture %s. SDL Error %s.\n", path, IMG_GetError());
        return NULL;
    }
    
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));
    new_text = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (new_text == NULL) {
        fprintf(stderr, "Can't create texture from %s. SDL error %s.\n", path, SDL_GetError());
        return NULL;
    }
    
    tex->width = loaded_surface->w;
    tex->height = loaded_surface->h;
    SDL_FreeSurface(loaded_surface);
    return tex;
}

void free_texture(Texture *t)
{
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        free(t);
    }
}

void texture_set_color(Texture *t, uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetTextureColorMod(t->texture, r, g, b);
}

void texture_set_blend_mode(Texture *t, SDL_BlendMode blend)
{
    SDL_SetTextureBlendMode(t->texture, blend);
}

void texture_set_alpha(Texture *t, uint8_t a)
{
    SDL_SetTextureAlphaMod(t->texture, a);
}

void render_texture(Texture *t, Coordinate pos, SDL_Renderer *renderer, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect render_quad = {pos.x, pos.y, t->width, t->height};
    
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, t->texture, clip, &render_quad, angle, center, flip);
}
