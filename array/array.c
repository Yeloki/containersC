//
// Created by Yeloki on 25.04.2022.
//

#include "array.h"


void array_init(array *arr) {
    arr->size = 0;
    arr->capacity = 0;
    arr->_min_capacity = 2;
    array_resize(arr, arr->_min_capacity);
}

void array_resize(array *arr, size_t n_size) {
    arr->data = realloc(arr->data, n_size);
    if (arr->data == NULL)
        Throw(ARRAY_MEMORY_ALLOCATION_ERROR);
    arr->capacity = n_size;
}

void array_push_back(array *arr, element el) {
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

element *array_data(array *arr) {
    return arr->data;
}

element array_at(array *arr, size_t index) {
    if (index >= arr->size)
        Throw(ARRAY_INDEX_OUT_OF_RANGE);
    return arr->data[index];
}

element *array_get(array *arr, size_t index) {
    if (index >= arr->size)
        Throw(ARRAY_INDEX_OUT_OF_RANGE);
    return &(arr->data[index]);
}

element array_front(array *arr) {
    return arr->data[0];
}

element array_back(array *arr) {
    return arr->data[arr->size - 1];
}

element *array_begin(array *arr) {
    return &(arr->data[0]);
}

element *array_end(array *arr) {
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
    arr->data = calloc(arr->_min_capacity, sizeof(element));
    arr->size = 0;
    arr->capacity = arr->_min_capacity;
}

element *array_insert(array *arr, size_t index, element el) {
    if (index <= arr->size)
        Throw(ARRAY_INDEX_OUT_OF_RANGE);
    if (arr->size == arr->capacity)
        array_resize(arr, arr->capacity * 2);

    element prev = arr->data[index];
    for (size_t i = index; i < arr->size; ++i) {
        element temp;
        temp = arr->data[i + 1];
        arr->data[i + 1] = prev;
        prev = temp;
    }
    arr->data[index] = el;
    return arr->data + index;
}

void array_erase(array *arr, element el) {
    element *temp = calloc(arr->capacity, sizeof(element));
    size_t n_size = 0;
    for (size_t i = 0; i < arr->size; ++i)
        if (arr->data[i] != el)
            temp[n_size++] = arr->data[i];
    free(arr->data);
    arr->data = temp;
    if (arr->size < arr->capacity / 2)
        array_resize(arr, arr->capacity / 2);
}

element pop_back(array *arr) {
    element el = arr->data[--arr->size];
    if (arr->size < arr->capacity / 2)
        array_resize(arr, arr->capacity / 2);
    return el;
}

void array_shrink_to_fit(array *arr) {
    array_resize(arr, arr->size);
}