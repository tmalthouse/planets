//
//  test_vector2d.c
//  planet
//
//  Created by Thomas Malthouse on 5/3/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include <stdbool.h>
#include "test_vector2d.h"
#include "../vector2d.h"


bool vector2d_test () {
    bool result = true;
    vector2d test_vector[] = {{5,5}, {1.0, -3.9}, {1e20, -1e-15}};
    
    int len = sizeof(test_vector)/sizeof(vector2d);
    
    //Test vectabs
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++) {
            if (vectabs(test_vector[i], test_vector[j]) >= -.001) {
                if (i==j && vectabs(test_vector[i], test_vector[j])>.001) {
                    result = false;//If there's a difference between identical vectors...
                }
            } else {
                result = false;//If the abs dist is neg
            }
        }
    }
    return result;
}