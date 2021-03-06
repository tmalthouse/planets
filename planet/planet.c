#include <math.h>
#include "planet.h"
#include "vector2d.h"
#include "coord.h"
#include "darray_types.h"

Vector2d gforce (CBody a, CBody b)
{
   double fnet = (BIG_G * a.mass * b.mass)/pow(absdist(a.pos, b.pos),2);
   double theta = atan2 ((b.pos.y-a.pos.y),(b.pos.x-a.pos.x));
   Vector2d x = {fnet*cos(theta), fnet*sin(theta)};
   return x;
}

void addforce (CBody *a, Vector2d force)
{
    a->fnet.x += force.x;
    a->fnet.y += force.y;
}

/*!
Sets the net force for each body in an array of cbodies.
Accepts a pointer to a dynamic array of cbodies.
Has O(n^2) speed--Will get slow with lots of bodies--I'll use a better algorithm eventually
*/
void calc_forces (Darray_CBody *bodies)
{
    CBody *planets = (bodies->data);
    Vector2d forcetable[bodies->len][bodies->len];

    for (int i=0; i<bodies->len; i++) {
        forcetable[i][i] = NULL_VECT;//Helps with debugging
        for (int j=i+1; j<bodies->len; j++) {
            Vector2d force = gforce(planets[i], planets[j]);
            forcetable[i][j] = force;
            forcetable[j][i] = force;
        }
    }
    for (int i=0; i<bodies->len; i++) {
        planets[i].fnet = (Vector2d){0, 0};//Set force to 0
        for (int j=0; j<bodies->len; j++) {
            if (i!=j) {//We really don't want to calc force to ourself--div/0 error
                addforce (planets+i, forcetable[i][j]);
            }
        }
        vdprintf("Net force on body %s is %f\n", planets[i].name, vectabs(planets[i].fnet, (Vector2d){0,0}));

    }
}


void cbody_update (Darray_CBody *bodies, double dt)
{
    calc_forces (bodies);

    //First, we change each body's velocity, using the forces calculated a line ago
    CBody *planets = bodies->data;
    for (int i=0; i<bodies->len; i++) {
        Vector2d acc;
        acc = (Vector2d){planets[i].fnet.x/planets[i].mass, planets[i].fnet.y/planets[i].mass};
        planets[i].vel = vectadd(planets[i].vel, vfmult(acc, dt));
    }

    //And then we change their positions based on their new velocities
    for (int i=0; i<bodies->len; i++) {
        planets[i].pos = vectadd(planets[i].pos, vfmult(planets[i].vel, dt));
    }
}

Coordinate absmaxpos (Darray_CBody *bodies) {
    Vector2d max = {0, 0};

    CBody *planets = bodies->data;
    for (int i=0; i<bodies->len; i++) {
        double x = fabs(planets[i].pos.x);
        double y = fabs(planets[i].pos.y);

        if (x>max.x) {
            max.x = x;
        }
        if (y>max.y) {
            max.y = y;
        }
    }
    dprintf("Max coord is (%f,%f)\n", max.x, max.y);
    return max;
}
