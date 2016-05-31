//
//  window.h
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef window_h
#define window_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "../coord.h"
#include "../debug.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int MAX_FPS;
extern SDL_Renderer *g_renderer;

typedef struct {
    bool status;
    SDL_Window *window;
    SDL_Renderer *renderer;
} ScreenComponents;

Vector2d screencoord (Vector2d spacecoord);
void screencoord_zoom (double direction);
void screencoord_set (Coordinate top_left, Coordinate bottom_left);
void screencoord_shift (int x, int y);


#endif /* window_h */
