//
//  vector2d.h
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef vector2d_h
#define vector2d_h

#include <float.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
} Vector2d;

#define NULL_VECT ((Vector2d){DBL_MAX,DBL_MAX})//This seems pretty safe--who'd ever need that exact huge vector? We can't use NAN or INF, since those don't compare.

double vectabs (Vector2d a, Vector2d b);
Vector2d vectadd (Vector2d a, Vector2d b);
Vector2d vfmult (Vector2d a, double k);
Vector2d atov2d (char *vect);
bool vect_eq (Vector2d a, Vector2d b);

#endif /* vector2d_h */
