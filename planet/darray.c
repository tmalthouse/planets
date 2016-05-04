#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Darray.h"

Darray *new_Darray (size_t element_size, int initial_count)
{
    Darray *arr = calloc (sizeof (Darray), 1);
    arr->entry_size = element_size;
    arr->len = initial_count;
    arr->cap = initial_count*2;
    arr->data = calloc (element_size, initial_count*2);
    if (arr->data != NULL) {
        return arr;
    }
    return NULL;
}

int Darray_expand (Darray *arr)
{
    void *temp = realloc (arr->data, arr->cap*2);
    if (temp != NULL) {
        arr->data = temp;
        return 0;
    }
    return -1;
}

int Darray_set (Darray *arr, void *data, int index)
{
    if (index > arr->cap) {
        return -1;
    }
    if (!memcpy (arr->data+(index*arr->entry_size), data, arr->entry_size)) {
        return 0;
    }
    return -1;
}

int Darray_append (Darray *arr, void *data)
{
    if (arr->len >= arr->cap) {
        if (Darray_expand (arr)) {
            return -1;
        }
    }
    if (Darray_set (arr, data, arr->len)) {
        return -1;
    }
    arr->len++;
    return 0;
}

void free_Darray (Darray *arr)
{
    free (arr->data);
    free (arr);
}