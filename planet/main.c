//
//  main.c
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include <errno.h>
#include "graphics/game.h"
#include "darray_types.h"
#include "file.h"
#include "color.h"

int main(int argc, const char * argv[]) {

    if (argc != 2) {
        printf("This program needs to be called with one argument:\n");
        printf("\t-Either a .sys file (generated on exit\n");
        printf("\t-Or with the word \"demo\"--This loads the inner solar system and a comet.\n");
        return -1;

    }

    Darray_CBody *bodies;
    int s = 0;
    if (!strcmp(argv[1], "demo")) {
        CBody sun = {"Sun", 1.988e30, 1, {20.0,0.0}, {0,0}, {0,0}, hex_to_color(COLOR_YELLOW)};
        CBody mercury = {"Mercury", 3.3e23, 1, {47362, 0}, {0,0}, {0,-5.7e10}, hex_to_color(COLOR_GRAY)};
        CBody venus = {"Venus", 4.87e24, 1, {0, 35002}, {0,0}, {1.08e11, 0}, hex_to_color(COLOR_ORANGE)};
        CBody earth = {"Earth", 5.97e24, 1, {-29780, 0}, {0,0}, {0, 1.49e11}, hex_to_color(COLOR_BLUE)};
        CBody mars = {"Mars", 6.42e23, 1, {0, -24000}, {0,0}, {-2.27e11, 0}, hex_to_color(COLOR_RED)};
        CBody jupiter = {"Jupiter", 1.89e27, 1, {-13070, 0}, {0,0}, {0, 7.41e11}, hex_to_color(COLOR_ORANGE)};
        CBody saturn = {"Saturn", 5.68e26, 1, {9690, 0}, {}, {0,-1.509e12}, hex_to_color(COLOR_YELLOW)};
        CBody uranus = {"Uranus", 8.68e25, 1, {6800, 0}, {}, {0,-2.875e12}, hex_to_color(COLOR_TEAL)};
        CBody neptune = {"Neptune", 1.02e26, 1, {5430, 0}, {}, {0,-4.504e12}, hex_to_color(COLOR_BLUE)};
        CBody pluto = {"Pluto", 1.3e23, 1, {6100, 0}, {}, {0,-4.436e12}, hex_to_color(COLOR_GRAY)};
        CBody comet = {"Comet", 3.3e10, 1, {66700, 0}, {0,0}, {0,-5.9e10}, hex_to_color(COLOR_WHITE)};

        bodies = new_darray_CBody(2);
        s+=darray_append_CBody(bodies, sun);
        s+=darray_append_CBody(bodies, mercury);
        s+=darray_append_CBody(bodies, venus);
        s+=darray_append_CBody(bodies, earth);
        s+=darray_append_CBody(bodies, mars);
        s+=darray_append_CBody(bodies, jupiter);
        s+=darray_append_CBody(bodies, saturn);
        s+=darray_append_CBody(bodies, uranus);
        s+=darray_append_CBody(bodies, neptune);
        s+=darray_append_CBody(bodies, pluto);
        s+=darray_append_CBody(bodies, comet);
        dprintf("%d\n", s);
    } else {
        FILE *src = fopen(argv[1], "r");
        if (src==NULL) {
            printf("File at %s can't be opened. Error: %s.\n", argv[1], strerror(errno));
            return -1;
        }
        bodies = loadsystem(src);
        fclose(src);
    }

    rungame(bodies);

    const char *saveloc = !strcmp(argv[1], "demo") ? "system.sys" : argv[1];//If we started from a file, overwrite that file. Otherwise, save it as default.

    FILE *sys = fopen(saveloc, "w");
    savesystem(bodies, sys);
    fclose(sys);

    return 0;
}
