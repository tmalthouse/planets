//
//  main.c
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "graphics/game.h"
#include "darray_types.h"

int main(int argc, const char * argv[]) {
    
    CBody sun = {"Sun", 1.988e30, 1, {0.0,0.0}, {0,0}, {0,0}};
    CBody mercury = {"Mercury", 3.3e23, 1, {47362, 0}, {0,0}, {0,-5.7e10}};
    CBody venus = {"Venus", 4.87e24, 1, {0, 35002}, {0,0}, {1.08e11, 0}};
    CBody earth = {"Earth", 5.97e24, 1, {-29780, 0}, {0,0}, {0, 1.49e11}};
    CBody mars = {"Mars", 6.42e23, 1, {0, -24000}, {0,0}, {-2.27e11, 0}};
    
    int s;
    Darray_CBody *bodies = new_darray_CBody(2);
    s+=darray_append_CBody(bodies, sun);
    s+=darray_append_CBody(bodies, mercury);
    s+=darray_append_CBody(bodies, venus);
    s+=darray_append_CBody(bodies, earth);
    s+=darray_append_CBody(bodies, mars);
    dprintf("%d\n", s);
    rungame(bodies);
    
    return 0;
}
