//
//  message.h
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef message_h
#define message_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdbool.h>
#include "texture.h"
#include "../coord.h"

typedef struct {
    char text[50];
    bool updated;
    Coordinate pos;
    TTF_Font *font;
    Texture tex;
    SDL_Renderer *renderer;
    uint64_t start_time;
    uint64_t duration;
} Message;

Message new_message(Coordinate pos, TTF_Font *f, SDL_Renderer *render);
void update_message(Message *m, char *str, uint64_t tick);
void render_message(Message *m, uint64_t tick);

#endif /* message_h */
