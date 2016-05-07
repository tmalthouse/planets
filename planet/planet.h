#ifndef PLANET_STRUCTS
#define PLANET_STRUCTS

#include "vector2d.h"
#include "coord.h"
#include "cbody.h"
#include "darray_types.h"

#define BIG_G (6.67e-11)


/*cbody function headers*/
vector2d gforce (cbody a, cbody b);
void addforce (cbody *a, vector2d force);
void calc_forces (Darray_cbody *bodies);

#endif /* end of include guard: PLANET_STRUCTS */
