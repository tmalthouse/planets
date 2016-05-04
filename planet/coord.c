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

void setpos (coordinate *c, int x, int y)
{
    c->x = x;
    c->y = y;
}

void changepos (coordinate *c, int x, int y)
{
    c->x+=x;
    c->y+=y;
}

double absdist (coordinate a, coordinate b)
{
    return vectabs (a, b);
}
