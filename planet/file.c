//
//  file.c
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include <stdio.h>
#include "file.h"
#include "darray.h"
#include "planet.h"

int savesystem (Darray *bodies, FILE *dest) {
    cbody *sys = (cbody*)(bodies->data);
    fprintf(dest, "SIZE:%d", bodies->len);
    for (int i=0; i<bodies->len; i++){
        fprintf(dest, "BODY:\n");
        fprintf(dest, "\tNAME:%s\n", sys[i].name);
        fprintf(dest, "\tMASS:%f\n", sys[i].mass);
        fprintf(dest, "\tRADIUS:%f\n", sys[i].radius);
        fprintf(dest, "\tVEL:{%f,%f}\n", sys[i].vel.x, sys[i].vel.y);
        fprintf(dest, "\tPOS:{%f,%f}\n", sys[i].pos.x, sys[i].pos.y);
        //We don't bother saving force because that's recalculated on load anyways.
    }
    return 0;
}