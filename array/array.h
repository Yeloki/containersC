//
// Created by Yeloki on 25.04.2022.
//

#ifndef CONTAINERS_ARRAY_H
#define CONTAINERS_ARRAY_H
#define DEBUG

#include <stdlib.h>
#include <stdbool.h>
#include "../exception.h"

#define ARRAY_INDEX_OUT_OF_RANGE  \
  ((struct SxTraceEntry) {300, 0, __FILE__, __LINE__, "\0", NULL})
#define ARRAY_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {301, 0, __FILE__, __LINE__, "\0", NULL})
#define ARRAY_IS_EMPTY  \
  ((struct SxTraceEntry) {302, 0, __FILE__, __LINE__, "\0", NULL})


typedef double array_el;

typedef struct {
    size_t _min_capacity;
    size_t size;
    size_t capacity;
    array_el *data;
} array;

void array_init(array *);

void array_resize(array *, size_t);

void array_push_back(array *, array_el);

void array_destroy(array *);

array_el *array_data(array *);

array_el array_at(array *, size_t);

array_el *array_get(array *, size_t);

array_el array_front(array *);

array_el array_back(array *);

array_el *array_begin(array *);

array_el *array_end(array *);

bool array_empty(array *);

size_t array_size(array *);

size_t array_capacity(array *);

void array_clear(array *);

array_el *array_insert(array *, size_t, array_el);

void array_erase(array *, array_el);

array_el pop_back(array *);

void array_shrink_to_fit(array *);

#ifdef DEBUG

void array_test_all();

#endif

#endif //CONTAINERS_ARRAY_H
