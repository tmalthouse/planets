//
//  cbody.h
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef cbody_h
#define cbody_h

#include "vector2d.h"
#include "coord.h"

typedef struct {
    char name[20];
    double mass;
    double radius;
    vector2d vel;
    vector2d fnet;
    coordinate pos;
} cbody;

#endif /* cbody_h */
