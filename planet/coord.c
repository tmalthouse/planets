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
