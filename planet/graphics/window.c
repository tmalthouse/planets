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
    SET_COORD,
    SC_SHIFT
};

static double calculate_ratio (Coordinate bottom_left, Coordinate top_right)
{
    double xratio = SCREEN_WIDTH/(bottom_left.x-top_right.x);
    double yratio = SCREEN_HEIGHT/(top_right.y-bottom_left.y);
    double ratio = (xratio < yratio)? yratio : xratio;//Set the ratio to the smaller of the two.
    printf("ratio is %.*f\n", 15, ratio);
    return ratio;
}

/*!
 These crazy functions right here translate space coordinates (the ones found in CBody.pos) to pixel locations for the screen. Calling screencoord (coordinate) actually does the calculation, while screencoord_set(coord) changes the ratio so an item at maxcoord is at the top right corner of the screen in all future calls.
 */

//Declared static so we don't pollute the namespace. This function should never be called directly, only through the wrappers below.
static Vector2d sc_core (enum SC_Mode mode, Vector2d spacecoord, double factor, Coordinate tr, Coordinate bl, int dx, int dy) {
    static Coordinate top_right, bottom_left;
    static long double ratio;
    
    switch (mode) {
        /*Handle setting coords (needs to be called at least once)*/
        case SET_COORD:
            top_right = tr;
            bottom_left = bl;
            ratio = calculate_ratio(bl, tr);
            return NULL_VECT;
        
        
        /*Handle changing scaling factor*/
        case SCALE:
            dprintf("Scaling factor is %f\n", factor);
            top_right = vfmult(top_right, factor);
            bottom_left = vfmult(bottom_left, factor);
            ratio = calculate_ratio(bottom_left, top_right);
            return NULL_VECT;
        
        case SC_SHIFT:
            {
                double x = (double)dx/ratio;
                double y = (double)dy/ratio;
                top_right.x += x;
                bottom_left.x += x;
                top_right.y += y;
                bottom_left.y += y;
            }
            break;
        
        case RETURN_COORD:
            break;//We just want to fall through
        default:
            break;
            
    }
    

    
    Vector2d screencoord = {(spacecoord.x-bottom_left.x)*ratio + SCREEN_WIDTH/2, (top_right.y-spacecoord.y)*ratio};
    vdprintf("screen x: %f, screen y: %f\n", screencoord.x, screencoord.y);
    
    return screencoord;
}

Vector2d screencoord (Vector2d spacecoord)
{
    return sc_core(RETURN_COORD, spacecoord, NAN, NULL_VECT, NULL_VECT, 0, 0);
}

void screencoord_zoom (double factor)
{
    dprintf("Scaling the screen by factor of %f\n", factor);
    sc_core(SCALE, NULL_VECT, factor, NULL_VECT, NULL_VECT, 0, 0);
}

void screencoord_set (Coordinate top_right, Coordinate bottom_left)
{
    sc_core(SET_COORD, NULL_VECT, NAN, top_right, bottom_left, 0, 0);
}

void screencoord_shift (int x, int y)
{
    sc_core(SC_SHIFT, NULL_VECT, NAN, NULL_VECT, NULL_VECT, x, y);
}
