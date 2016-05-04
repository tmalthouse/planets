#ifndef DATASTRUCT_Darray
#define DATASTRUCT_Darray

#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    uint8_t *data; //We store the data as a byte array, and putting it at the beginning lets us do hacky casts
    int len;
    int cap;
    size_t entry_size;
} Darray;

Darray *new_Darray (size_t element_size, int initial_count);
int Darray_expand (Darray *arr);
int Darray_set (Darray *arr, void *data, int index);
int Darray_append (Darray *arr, void *data);
void free_Darray (Darray *arr);

#endif /* end of include guard: DATASTRUCT_Darray */
