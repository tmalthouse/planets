//
//  file.c
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "planet.h"
#include "darray_types.h"

int savesystem (Darray_cbody *bodies, FILE *dest)
{
    cbody *sys = (cbody*)(bodies->data);
    fprintf(dest, "SIZE:%d", bodies->len);
    for (int i=0; i<bodies->len; i++){
        fprintf(dest, "BODY{\n");
        fprintf(dest, "\tNAME:%s\n", sys[i].name);
        fprintf(dest, "\tMASS:%f\n", sys[i].mass);
        fprintf(dest, "\tRADIUS:%f\n", sys[i].radius);
        fprintf(dest, "\tVEL:{%f,%f}\n", sys[i].vel.x, sys[i].vel.y);
        fprintf(dest, "\tPOS:{%f,%f}\n", sys[i].pos.x, sys[i].pos.y);
        fprintf(dest, "}\n");
        //We don't bother saving force because that's recalculated on load anyways.
    }
    return 0;
}

cbody loadbody (char *bodydef)
{
    cbody result;
    
    //Do the name
    char *name = strchr(bodydef, ':');//Find the start of "name"
    char *nameend = strchr(name, '\n');//And find the \n at the end
    memcpy(&result.name, name+1, nameend-name); //Copy it into the struct we made, starting from the first char. We copy the \n as well.
    nameend = strchr(result.name, '\n');
    nameend = '\0';
    
    //Do the mass
    char *mass = strchr(name+1, ':')+1;
    result.mass = atof(mass);
    
    //Do the radius
    char *rad = strchr(mass+1, ':')+1;
    result.radius = atof(rad);
    
    //Do the vel
    char *vel = strchr(rad+1, ':')+1;
    result.vel = atov2d(vel);
    
    //Do the pos
    char *pos = strchr(vel+1, ':')+1;
    result.pos = atov2d(pos);
    
    return result;
}

Darray_cbody *loadsystem (FILE *src)
{
    Darray_cbody *sys = new_darray_cbody(10);
    
    //Find the size of the file in bytes
    fseek (src, 0L, SEEK_END);
    size_t size = ftell (src);
    rewind (src);
    
    //Copy it to a buffer
    char *buf = calloc (size, sizeof(char));
    fgets(buf, sizeof(char)*(int)size, src);
    
    //Load bodies, delimiting on { tokens
    char *body = strchr(buf, '{')+1;
    while (body!=NULL) {
        darray_append_cbody(sys, loadbody(body));
        body = strchr(body, '{')+1;
    }
    
    free(buf);
    return sys;
}




