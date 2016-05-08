//
//  window.c
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include <math.h>
#include "window.h"
#include "../debug.h"

SDL_Renderer *g_renderer = NULL;

//I'm comfortable declaring the screen dims (but not the system maxcoords) as global, since there's always only one screen per program instance, but potentially multiple systems simultaneously at some point.
int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 720;

int MAX_FPS = 100;


/*!
 These crazy functions right here translate space coordinates (the ones found in cbody.pos) to pixel locations for the screen. Calling screencoord (coordinate) actually does the calculation, while screencoord_set(coord) changes the ratio so an item at maxcoord is at the top right corner of the screen in all future calls.
 */

//Declared static so we don't pollute the namespace. This function should never be called directly, only through the wrappers below.
static Vector2d sc_core (Vector2d spacecoord, Vector2d maxcoord) {
    static long double ratio = NAN;//We want the ratio to persist over multiple calls--a bit like a closure but we only need one.
    
    if (!vect_eq(maxcoord, NULL_VECT)) {//The only time this bit should be called is if we're calling screencoord_set
        long double xratio = SCREEN_WIDTH/(2*maxcoord.x);//0,0 is in the middle of the screen in space coordinates, but in the top left in screen coords.
        long double yratio = SCREEN_HEIGHT/(2*maxcoord.y);
        
        ratio = ((xratio<yratio)?xratio:yratio)*0.9;//Set the ratio to the smaller of the two, plus a bit of fudge factor.
        dprintf("ratio set to %Lf \n", ratio);
        return NULL_VECT;//This bit only gets called when wrappen in a void function anyways.
    }
    
    //ratio = SCREEN_HEIGHT/1e12;
    Vector2d screencoord = {((float)SCREEN_WIDTH/2)+spacecoord.x*ratio,
        ((float)SCREEN_HEIGHT/2)+spacecoord.y*ratio};
    
    dprintf("screen x: %f, screen y: %f\n", screencoord.x, screencoord.y);
    return screencoord;
}

Vector2d screencoord (Vector2d spacecoord)
{
    return sc_core(spacecoord, NULL_VECT);
}

void screencoord_set (Vector2d absmax)
{
    dprintf("Setting max values for the screen size conversion. x=%f, y=%f\n",absmax.x, absmax.y);
    sc_core(NULL_VECT, absmax);
}

