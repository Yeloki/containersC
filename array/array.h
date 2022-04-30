//
// Created by Yeloki on 25.04.2022.
//

#ifndef CONTAINERS_ARRAY_H
#define CONTAINERS_ARRAY_H
#define DEBUG

#include <stdlib.h>
#include <stdbool.h>
#include "../exception/exception.h"

#define ARRAY_INDEX_OUT_OF_RANGE  \
  ((struct SxTraceEntry) {300, 0, __FILE__, __LINE__, "\0", NULL})
#define ARRAY_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {301, 0, __FILE__, __LINE__, "\0", NULL})
#define ARRAY_IS_EMPTY  \
  ((struct SxTraceEntry) {302, 0, __FILE__, __LINE__, "\0", NULL})
#define ARRAY_ITERATOR_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {303, 0, __FILE__, __LINE__, "\0", NULL})
#define ARRAY_ITERATOR_ITERATOR_OUT_OF_ARRAY  \
  ((struct SxTraceEntry) {304, 0, __FILE__, __LINE__, "\0", NULL})
#define ARRAY_ITERATOR_DIFFERENT_ARRAY_POINTERS  \
  ((struct SxTraceEntry) {305, 0, __FILE__, __LINE__, "\0", NULL})
typedef double array_el;

typedef struct {
    size_t _min_capacity;
    size_t size;
    size_t capacity;
    array_el *data;
} array;

void arrayInit(array *);

void arrayResize(array *, size_t);

void arrayPushBack(array *, array_el);

void arrayDestroy(array *);

array_el *arrayData(array *);

array_el arrayAt(array *, size_t);

array_el *arrayGet(array *, size_t);

array_el arrayFront(array *);

array_el arrayBack(array *);

bool arrayEmpty(array *);

size_t arraySize(array *);

size_t arrayCapacity(array *);

void arrayClear(array *);

array_el *arrayInsert(array *, size_t, array_el);

void arrayErase(array *, array_el);

array_el arrayPopBack(array *);

void arrayShrinkToFit(array *);


typedef struct {
    array *arr;
    array_el *curr;
} array_iter;

array_iter *arrayIterInIt(array *, array_el *);

void arrayIterDestroy(array_iter *);

array_el *arrayIterNext(array_iter *);

array_el *arrayIterCurr(array_iter *);

array_el *arrayIterPrev(array_iter *);

array_el *arrayIterAt(array_iter *, size_t);

array_el *arrayIterGoTo(array_iter *, size_t);

bool arrayIterIsEqual(array_iter *, array_iter *);

bool arrayIterIsNotEqual(array_iter *, array_iter *);

bool arrayIterIsMore(array_iter *, array_iter *);

bool arrayIterIsEqOrMore(array_iter *, array_iter *);

bool arrayIterIsLess(array_iter *, array_iter *);

bool arrayIterIsEqOrLess(array_iter *, array_iter *);

// iterator functions for array
array_iter *arrayBegin(array *);

array_iter *arrayEnd(array *);

#ifdef DEBUG

void arrayTestAll();

#endif

#endif //CONTAINERS_ARRAY_H
