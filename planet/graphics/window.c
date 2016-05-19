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

int MAX_FPS = 60;

enum SC_Mode {
    RETURN_COORD,
    SCALE,
    SET_COORD
};

static double calculate_ratio (Coordinate bottom_right, Coordinate top_left)
{
    double xratio = SCREEN_WIDTH/(bottom_right.x-top_left.x);
    double yratio = SCREEN_HEIGHT/(bottom_right.y-top_left.y);
    double ratio = (xratio < yratio)? yratio : xratio;//Set the ratio to the smaller of the two.
    printf("ratio is %f\n", ratio);
    return ratio;
}

/*!
 These crazy functions right here translate space coordinates (the ones found in CBody.pos) to pixel locations for the screen. Calling screencoord (coordinate) actually does the calculation, while screencoord_set(coord) changes the ratio so an item at maxcoord is at the top right corner of the screen in all future calls.
 */

//Declared static so we don't pollute the namespace. This function should never be called directly, only through the wrappers below.
static Vector2d sc_core (enum SC_Mode mode, Vector2d spacecoord, double factor, Coordinate tl, Coordinate br) {
    static Coordinate top_left, bottom_right;
    static double ratio;
    
    switch (mode) {
        /*Handle setting coords (needs to be called at least once)*/
        case SET_COORD:
            top_left = tl;
            bottom_right = br;
            ratio = calculate_ratio(br, tl);
            return NULL_VECT;
        
        
        /*Handle changing scaling factor*/
        case SCALE:
            dprintf("Scaling factor is %f\n", factor);
            top_left = vfmult(top_left, factor);
            bottom_right = vfmult(bottom_right, factor);
            ratio = calculate_ratio(bottom_right, top_left);
            return NULL_VECT;
        
        case RETURN_COORD:
            break;//We just want to fall through
        default:
            break;
            
    }
    Vector2d screencoord = {((float)SCREEN_WIDTH/2)+spacecoord.x*ratio,
        ((float)SCREEN_HEIGHT/2)+spacecoord.y*ratio};
    vdprintf("screen x: %f, screen y: %f\n", screencoord.x, screencoord.y);
    return screencoord;
}

Vector2d screencoord (Vector2d spacecoord)
{
    return sc_core(RETURN_COORD, spacecoord, NAN, NULL_VECT, NULL_VECT);
}

void screencoord_zoom (double factor)
{
    dprintf("Scaling the screen by factor of %f\n", factor);
    sc_core(SCALE, NULL_VECT, factor, NULL_VECT, NULL_VECT);
}

void screencoord_set ( Coordinate top_left, Coordinate bottom_right)
{
    sc_core(SET_COORD, NULL_VECT, NAN, top_left, bottom_right);
}
