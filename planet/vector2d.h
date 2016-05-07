//
//  vector2d.h
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef vector2d_h
#define vector2d_h

typedef struct {
    double x;
    double y;
} vector2d;

double vectabs (vector2d a, vector2d b);
vector2d vectadd (vector2d a, vector2d b);
vector2d vfmult (vector2d a, double k);
vector2d atov2d (char *vect);

#endif /* vector2d_h */
