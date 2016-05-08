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

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern SDL_Renderer *g_renderer;

vector2d screencoord (vector2d spacecoord);
void screencoord_set (vector2d maxcoord);


#endif /* window_h */
