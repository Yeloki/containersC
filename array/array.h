//
// Created by Yeloki on 25.04.2022.
//

#ifndef CONTAINERS_ARRAY_H
#define CONTAINERS_ARRAY_H
#define DEBUG

#include <stdlib.h>
#include <stdbool.h>
#include "../exception/exceptions_list.h"

typedef void *array_el;

typedef struct {
  size_t _min_capacity;
  size_t size;
  size_t capacity;
  array_el *data;
} array;

array *arrayInit();

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

/// for char array

void arrayPushBackChar(array *arr, char c);

char arrayPopBackChar(array *arr);

char arrayAtChar(array* arr, size_t index);

#endif //CONTAINERS_ARRAY_H
