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

typedef vector2d coordinate;

void setpos (coordinate *c, int x, int y);
void changepos (coordinate *c, int x, int y);
double absdist (coordinate a, coordinate b);


#endif /* coord_h */
