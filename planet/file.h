//
//  file.h
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#ifndef file_h
#define file_h

#include <stdio.h>
#include "darray_types.h"

int savesystem (Darray_CBody *bodies, FILE *dest);
Darray_CBody *loadsystem (FILE *src);

#endif /* file_h */
