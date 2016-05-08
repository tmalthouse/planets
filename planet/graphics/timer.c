//
//  timer.c
//  planet
//
//  Created by Thomas Malthouse on 5/8/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "timer.h"
#include <SDL2/SDL.h>

Timer new_timer()
{
    return (Timer){0, false};
}

void start_timer(Timer *t)
{
    t->started = true;
    t->start = SDL_GetTicks();
}

void stop_timer(Timer *t)
{
    t->started = false;
}

uint64_t get_time(Timer *t)
{
    if (t->started) {
        return SDL_GetTicks()-t->start;
    }
    return 0;
}