//
// Created by Yeloki on 25.04.2022.
//

#ifndef CONTAINERS_ARRAY_H
#define CONTAINERS_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include "../CException.h"

enum ERRORS {
    ARRAY_MEMORY_ALLOCATION_ERROR,
    ARRAY_INDEX_OUT_OF_RANGE
};


typedef double element;

typedef struct {
    size_t _min_capacity;
    size_t size;
    size_t capacity;
    element *data;
} array;

void array_init(array *);

void array_resize(array *, size_t);

void array_push_back(array *, element);

void array_destroy(array *);

element *array_data(array *);

element array_at(array *, size_t);

element *array_get(array *, size_t);

element array_front(array *);

element array_back(array *);

element *array_begin(array *);

element *array_end(array *);

bool array_empty(array *);

size_t array_size(array *);

size_t array_capacity(array *);

void array_clear(array *);

element *array_insert(array *, size_t, element);

void array_erase(array *, element);

element pop_back(array *);

void array_shrink_to_fit(array *);


#endif //CONTAINERS_ARRAY_H
