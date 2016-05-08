//
//  coord.c
//  planet
//
//  Created by Thomas Malthouse on 5/4/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "planet.h"

void setpos (Coordinate *c, int x, int y)
{
    c->x = x;
    c->y = y;
}

void changepos (Coordinate *c, int x, int y)
{
    c->x+=x;
    c->y+=y;
}

double absdist (Coordinate a, Coordinate b)
{
    return vectabs (a, b);
}
