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
    Darray_CBody *bodies = new_darray_CBody(5);
    darray_append_CBody(bodies, (CBody){"Test", 5, 5, {20,20}, {0,0}, {-30, -30}});
    rungame(bodies);
    
    return 0;
}
