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
#include "color.h"

int savesystem (Darray_CBody *bodies, FILE *dest)
{
    CBody *sys = (CBody*)(bodies->data);
    fprintf(dest, "SIZE=%d\n", bodies->len);
    for (int i=0; i<bodies->len; i++){
        fprintf(dest, "BODY[\n");
        fprintf(dest, "\tNAME=%s\n", sys[i].name);
        fprintf(dest, "\tMASS=%f\n", sys[i].mass);
        fprintf(dest, "\tRADIUS=%f\n", sys[i].radius);
        fprintf(dest, "\tVEL={%f,%f}\n", sys[i].vel.x, sys[i].vel.y);
        fprintf(dest, "\tPOS={%f,%f}\n", sys[i].pos.x, sys[i].pos.y);
        fprintf(dest, "\tCOLOR=%d\n", color_hex(sys[i].color));
        fprintf(dest, "]\n");
        //We don't bother saving force because that's recalculated on load anyways.
    }
    return 0;
}

CBody loadbody (char *bodydef)
{
    CBody result;

    //Do the name
    char *name = strchr(bodydef, '=')+1;//Find the start of "name"
    char *nameend = strchr(bodydef+5, '\n');//Find the end of the string
    dprintf("start is %p, end is %p\n", name, nameend);
    strncpy(result.name, name, nameend-name);
    result.name[nameend-name] = '\0';//We need to add the \0 ourselves, since the source string is terminated by \n
    dprintf("The name is %s\n", result.name);

    //Do the mass
    char *mass = strchr(name+1, '=')+1;
    result.mass = atof(mass);

    //Do the radius
    char *rad = strchr(mass+1, '=')+1;
    result.radius = atof(rad);

    //Do the vel
    char *vel = strchr(rad+1, '=')+1;
    result.vel = atov2d(vel);

    //Do the pos
    char *pos = strchr(vel+1, '=')+1;
    result.pos = atov2d(pos);

    char *col = strchr(pos+1, '=')+1;
    result.color = hex_color(atoi(col));

    return result;
}

Darray_CBody *loadsystem (FILE *src)
{
    Darray_CBody *sys = new_darray_CBody(10);

    //Find the size of the file in bytes
    fseek (src, 0L, SEEK_END);
    size_t size = ftell (src);
    rewind (src);

    //Copy it to a buffer
    char *buf = calloc (size+1, sizeof(char));
    if (fread(buf, sizeof(char), (int)size+1, src)) {
        fprintf(stderr, "Couldn't read the file!\n");
        return NULL;
    }

    buf[size] = '\0';//Since we use fread instead of fgets, we need to add the null ourselves

    //Load bodies, delimiting on [ tokens
    char *body = strchr(buf, '[')+3;
    while (body!=NULL) {
        body++;
        darray_append_CBody(sys, loadbody(body));
        dprintf("body is %d\t\n", body==NULL);
        body = strchr(body, '[');
    }

    free(buf);
    return sys;
}
