//
// Created by Yeloki on 25.04.2022.
//

#include "array.h"
#include <assert.h>


void array_init(array *arr) {
    arr->size = 0;
    arr->capacity = 2;
    arr->_min_capacity = 2;
    arr->data = malloc(arr->capacity * sizeof (array_el));
}

void array_resize(array *arr, size_t n_size) {
    arr->data = realloc(arr->data, n_size * sizeof(array_el));
    if (arr->data == NULL)
        Throw(ARRAY_MEMORY_ALLOCATION_ERROR);
    arr->capacity = n_size;
}

void array_push_back(array *arr, array_el el) {
    if (arr->size == arr->capacity)
        array_resize(arr, arr->capacity * 2);
    arr->data[(arr->size)++] = el;
}

void array_destroy(array *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

array_el *array_data(array *arr) {
    return arr->data;
}

array_el array_at(array *arr, size_t index) {
    if (index >= arr->size)
        Throw(ARRAY_INDEX_OUT_OF_RANGE);
    return arr->data[index];
}

array_el *array_get(array *arr, size_t index) {
    if (index >= arr->size)
        Throw(ARRAY_INDEX_OUT_OF_RANGE);
    return &(arr->data[index]);
}

array_el array_front(array *arr) {
    return arr->data[0];
}

array_el array_back(array *arr) {
    return arr->data[arr->size - 1];
}

array_el *array_begin(array *arr) {
    return &(arr->data[0]);
}

array_el *array_end(array *arr) {
    return arr->data + arr->size;
}

bool array_empty(array *arr) {
    return !arr->size;
}

size_t array_size(array *arr) {
    return arr->size;
}

size_t array_capacity(array *arr) {
    return arr->capacity;
}

void array_clear(array *arr) {
    free(arr->data);
    arr->data = calloc(arr->_min_capacity, sizeof(array_el));
    arr->size = 0;
    arr->capacity = arr->_min_capacity;
}

array_el *array_insert(array *arr, size_t index, array_el el) {
    if (index <= arr->size)
        Throw(ARRAY_INDEX_OUT_OF_RANGE);
    if (arr->size == arr->capacity)
        array_resize(arr, arr->capacity * 2);

    array_el prev = arr->data[index];
    for (size_t i = index; i < arr->size; ++i) {
        array_el temp;
        temp = arr->data[i + 1];
        arr->data[i + 1] = prev;
        prev = temp;
    }
    arr->data[index] = el;
    return arr->data + index;
}

void array_erase(array *arr, array_el el) {
    array_el *temp = calloc(arr->capacity, sizeof(array_el));
    size_t n_size = 0;
    for (size_t i = 0; i < arr->size; ++i)
        if (arr->data[i] != el)
            temp[n_size++] = arr->data[i];
    free(arr->data);
    arr->data = temp;
    if (arr->size < arr->capacity / 2)
        array_resize(arr, arr->capacity / 2);
}

array_el pop_back(array *arr) {
    array_el el = arr->data[--arr->size];
    if (arr->size < arr->capacity / 2)
        array_resize(arr, arr->capacity / 2);
    return el;
}

void array_shrink_to_fit(array *arr) {
    array_resize(arr, arr->size);
}

#ifdef DEBUG

void array_test_all() {
    {
        array array1;
        array_init(&array1);
        for (double el = 0; el < 100; el += 1)
            array_push_back(&array1, el);
        assert(array_size(&array1) == 100);
        double el = 0;
        for (int i = 0; i < 100; ++i, el += 1) {
            assert(el == array_at(&array1, i));
        }
    }
}

#endif