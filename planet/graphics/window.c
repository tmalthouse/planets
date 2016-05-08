//
//  window.c
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include <math.h>
#include "window.h"
#include "../coord.h"
#include "../vector2d.h"

SDL_Renderer *g_renderer = NULL;

//I'm comfortable declaring the screen dims (but not the system maxcoords) as global, since there's always only one screen per program instance, but potentially multiple systems simultaneously at some point.
int SCREEN_WIDTH = 300;
int SCREEN_HEIGHT = 300;


/*!
 These crazy functions right here translate space coordinates (the ones found in cbody.pos) to pixel locations for the screen. Calling screencoord (coordinate) actually does the calculation, while screencoord_set(coord) changes the ratio so an item at maxcoord is at the top right corner of the screen in all future calls.
 */

//Declared static so we don't pollute the namespace. This function should never be called directly, only through the wrappers below.
static Vector2d sc_core (Vector2d spacecoord, Vector2d maxcoord) {
    static double ratio = NAN;//We want the ratio to persist over multiple calls--a bit like a closure but we only need one.
    
    if (!vect_eq(maxcoord, NULL_VECT)) {//The only time this bit should be called is if we're calling screencoord_set
        double xratio = SCREEN_WIDTH/(2*maxcoord.x);//0,0 is in the middle of the screen in space coordinates, but in the top left in screen coords.
        double yratio = SCREEN_HEIGHT/(2*maxcoord.y);
        
        ratio = (xratio<yratio)?xratio:yratio;//Set the ratio to the smaller of the two.
        return NULL_VECT;//This bit only gets called when wrappen in a void function anyways.
    }
    
    Vector2d screencoord = {((float)SCREEN_WIDTH/2)+spacecoord.x*ratio,
        ((float)SCREEN_HEIGHT/2)+spacecoord.y*ratio};
    
    printf("screen x: %f, screen y: %f\n", screencoord.x, screencoord.y);
    return screencoord;
}

Vector2d screencoord (Vector2d spacecoord)
{
    return sc_core(spacecoord, NULL_VECT);
}

void screencoord_set (Vector2d absmax)
{
    sc_core(NULL_VECT, absmax);
}

