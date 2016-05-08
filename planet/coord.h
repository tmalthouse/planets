//
//  coord.h
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef coord_h
#define coord_h

#include "vector2d.h"

typedef Vector2d Coordinate;

void setpos (Coordinate *c, int x, int y);
void changepos (Coordinate *c, int x, int y);
double absdist (Coordinate a, Coordinate b);


#endif /* coord_h */
