#include <math.h>
#include "planet.h"

double vectabs (vector2d a, vector2d b) {
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

vector2d vectadd (vector2d a, vector2d b)
{
    return (vector2d){a.x+b.x, a.y+b.y};
}

vector2d vfmult (vector2d a, double k) {
    return (vector2d){a.x*k, a.y*k};
}