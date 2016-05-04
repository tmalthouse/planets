#ifndef PLANET_STRUCTS
#define PLANET_STRUCTS

#include "darray.h"
#include "vector2d.h"
#include "coord.h"

#define BIG_G (6.67e-11)



typedef struct {
    char name[20];
    double mass;
    double radius;
    vector2d vel;
    vector2d fnet;
    coordinate pos;
} cbody;


/*cbody function headers*/
vector2d gforce (cbody a, cbody b);
void addforce (cbody *a, vector2d force);
void calc_forces (Darray *bodies);

#endif /* end of include guard: PLANET_STRUCTS */
