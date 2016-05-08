#include <math.h>
#include <string.h>
#include "planet.h"
#include "vector2d.h"

double vectabs (Vector2d a, Vector2d b) {
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

Vector2d vectadd (Vector2d a, Vector2d b)
{
    return (Vector2d){a.x+b.x, a.y+b.y};
}

Vector2d vfmult (Vector2d a, double k) {
    return (Vector2d){a.x*k, a.y*k};
}

Vector2d atov2d (char *vect) {
    char *start = strchr(vect, '{');
    char *delim = strchr(vect, ',');
    return (Vector2d){atof(start+1),atof(delim+1)};
}

bool vect_eq (Vector2d a, Vector2d b)
{
    return (a.x==b.x)&&(a.y==b.y);
}