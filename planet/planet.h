#ifndef PLANET_STRUCTS
#define PLANET_STRUCTS

#include "vector2d.h"
#include "coord.h"
#include "cbody.h"
#include "darray_types.h"

#define BIG_G (6.67e-11)
#define ONE_HOUR (60*60)
#define ONE_DAY (ONE_HOUR*24)



/*cbody function headers*/
Vector2d gforce (CBody a, CBody b);
void addforce (CBody *a, Vector2d force);
void calc_forces (Darray_CBody *bodies);
void cbody_update (Darray_CBody *bodies, double dt);
Coordinate absmaxpos (Darray_CBody *bodies);

#endif /* end of include guard: PLANET_STRUCTS */
