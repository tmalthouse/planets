//
//  message.c
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "message.h"
#include <string.h>

Message new_message(Coordinate position, TTF_Font *f, SDL_Renderer *render)
{
    Message a = {.text = " ", .pos = position, .font = f, .renderer = render, .duration = 2000};
    return a;
}

void update_message(Message *m, char *str, uint64_t tick)
{
    strncpy(m->text, str, 50);
    
    m->start_time = tick;
    m->updated = true;
}

void render_message(Message *m, uint64_t tick)
{
    //dprintf("Trying to render message.\n");
    if (tick-m->start_time > m->duration){
        return;
    }
    
    if (m->updated || m->tex.texture == NULL) {
        dprintf("Updating message\n");
        m->updated = false;
        SDL_Surface *text_surf = TTF_RenderText_Blended(m->font, m->text, (SDL_Color){0xFF, 0xFF, 0xFF, 0x00});
        if (text_surf == NULL) {
            fprintf(stderr, "Can't render text! SDL error:%s\n", TTF_GetError());
            return;
        }
        
        m->tex.texture = SDL_CreateTextureFromSurface(m->renderer, text_surf);
        m->tex.height = text_surf->h;
        m->tex.width = text_surf->w;
        free(text_surf);
    }
    
    render_texture(&m->tex, m->pos, m->renderer, RENDER_DEFAULT_ARGS);
}