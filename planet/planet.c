#include <math.h>
#include "planet.h"
#include "vector2d.h"
#include "coord.h"
#include "darray_types.h"

vector2d gforce (cbody a, cbody b)
{
   double fnet = (BIG_G * a.mass * b.mass)/pow(absdist(a.pos, b.pos),2);
   double theta = atan ((b.pos.y-a.pos.y)/(b.pos.x-a.pos.x));
   vector2d x = {fnet*cos(theta), fnet*sin(theta)};
   return x;
}

void addforce (cbody *a, vector2d force)
{
    a->fnet.x += force.x;
    a->fnet.y += force.y;
}

/*!
Sets the net force for each body in an array of cbodies.
Accepts a pointer to a dynamic array of cbodies.
Has O(n^2) speed--Will get slow with lots of bodies--I'll use a better algorithm eventually
*/
void calc_forces (Darray_cbody *bodies)
{
    cbody *planets = (bodies->data);
    for (int i=0; i<bodies->len; i++) {
        planets[i].fnet = (vector2d){0, 0};//Set force to 0
        for (int j=0; j<bodies->len; j++) {
            if (i!=j) {//We really don't want to calc force to ourself--div/0 error
                addforce (&planets[i], gforce(planets[i], planets[j]));
            }
        }
    }
}


void cbody_update (Darray_cbody *bodies, double dt)
{
    calc_forces (bodies);
    
    //First, we change each body's velocity, using the forces calculated a line ago
    cbody *planets = bodies->data;
    for (int i=0; i<bodies->len; i++) {
        vector2d acc;
        acc = (vector2d){planets[i].fnet.x/planets[i].mass, planets[i].fnet.y/planets[i].mass};
        planets[i].vel = vectadd(planets[i].vel, vfmult(acc, dt));
    }
    
    //And then we change their positions based on their new velocities
    for (int i=0; i<bodies->len; i++) {
        planets[i].pos = vectadd(planets[i].pos, vfmult(planets[i].vel, dt));
    }
}