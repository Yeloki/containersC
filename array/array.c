//
// Created by Yeloki on 25.04.2022.
//

#include "array.h"
#include <assert.h>


void array_init(array *arr) {
    arr->size = 0;
    arr->capacity = 2;
    arr->_min_capacity = 2;
    arr->data = malloc(arr->capacity * sizeof(array_el));
    if (arr->data == NULL)
        throw(ARRAY_MEMORY_ALLOCATION_ERROR);
}

void array_resize(array *arr, size_t n_size) {
    arr->data = realloc(arr->data, n_size * sizeof(array_el));
    if (arr->data == NULL)
        throw(ARRAY_MEMORY_ALLOCATION_ERROR);
    for (size_t i = arr->size; i < n_size; ++i)
        arr->data[i] = 0;
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
        throw(ARRAY_INDEX_OUT_OF_RANGE);
    return arr->data[index];
}

array_el *array_get(array *arr, size_t index) {
    if (index >= arr->size)
        throw(ARRAY_INDEX_OUT_OF_RANGE);
    return &(arr->data[index]);
}

array_el array_front(array *arr) {
    return arr->data[0];
}

array_el array_back(array *arr) {
    return arr->data[arr->size - 1];
}

array_el *array_begin(array *arr) {
    return arr->data;
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
    if (index >= arr->size)
        throw(ARRAY_INDEX_OUT_OF_RANGE);
    if (arr->size == arr->capacity)
        array_resize(arr, arr->capacity * 2);

    array_el prev = arr->data[index];
    for (size_t i = index; i < arr->size; ++i) {
        array_el temp;
        temp = arr->data[i + 1];
        arr->data[i + 1] = prev;
        prev = temp;
    }
    ++arr->size;
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
    arr->size = n_size;
    if (arr->size < arr->capacity / 2)
        array_resize(arr, arr->capacity / 2);
}

array_el pop_back(array *arr) {
    if (arr->size == 0)
        throw(ARRAY_IS_EMPTY);
    array_el el = arr->data[--arr->size];
    if (arr->size < arr->capacity / 2)
        array_resize(arr, arr->capacity / 2);
    return el;
}

void array_shrink_to_fit(array *arr) {
    if (arr->size <= arr->_min_capacity)
        array_resize(arr, arr->_min_capacity);
    else
        array_resize(arr, arr->size);
}

#ifdef DEBUG

void array_test_all() {
    {
        /// test push_back, resize and at
        array array1;
        array_init(&array1);
        for (size_t el = 0; el < 100; ++el)
            array_push_back(&array1, (double) el);
        assert(array_size(&array1) == 100);
        for (int i = 0; i < 100; ++i) {
            assert((double) i == array_at(&array1, i));
        }
        assert(array_capacity(&array1) == 128);
        array_destroy(&array1);
    }
    {
        /// test throw index error
        array array1;
        array_init(&array1);
        array_resize(&array1, 64);
        bool flag = 0;
        try {
            array_get(&array1, 64);
        } catch(ARRAY_INDEX_OUT_OF_RANGE.code) {
            flag = true;
        }
        endtry
        assert(flag);
        array_destroy(&array1);
    }
    {
        /// test throw memory allocation error
        array array1;
        array_init(&array1);
        array_resize(&array1, 64);
        bool flag = 0;
        try {
            array_resize(&array1, (size_t) 1e18);
        } catch(ARRAY_MEMORY_ALLOCATION_ERROR.code) {
            flag = true;
        }
        endtry
        assert(flag);
        array_destroy(&array1);
    }
    {
        /// test front, back, get, empty & clear
        array array1;
        array_init(&array1);
        for (size_t i = 50; i < 100; ++i)
            array_push_back(&array1, (double) i);
        assert(array_front(&array1) == 50);
        assert(array_back(&array1) == 99);
        assert(*array_get(&array1, 22) == array_at(&array1, 22));
        assert(!array_empty(&array1));
        array_clear(&array1);
        assert(array_empty(&array1));
    }
    {
        /// test data, shrink_to_fit, begin & end
        array array1;
        array_init(&array1);
        for (size_t i = 0; i < 100; ++i)
            array_push_back(&array1, (double) i);
        assert(array_data(&array1) == array1.data);
        array_shrink_to_fit(&array1);
        assert(array1.capacity == array1.size);
        assert(array_begin(&array1) == array1.data);
        assert(array_end(&array1) == array1.data + 100);
        array_destroy(&array1);
    }
    {
        /// test insert
        array array1;
        array_init(&array1);
        for (size_t i = 0; i < 100; ++i)
            array_push_back(&array1, (double) i);
        array_insert(&array1, 20, 104);
        assert(array1.size == 101);
        assert(*array_get(&array1, 20) == 104);
        array_destroy(&array1);
    }
    {
        /// test erase & pop_back
        array array1;
        array_init(&array1);
        for (size_t i = 0; i < 100; ++i)
            array_push_back(&array1, (double) i);
        for (size_t i = 1; i < 100; i += 5)
            array_insert(&array1, i, 20);
        array_erase(&array1, 20);
        assert(array1.size == 99);
        assert(pop_back(&array1) == 99);
        assert(array1.size == 98);
        array_destroy(&array1);
    }
}


#endif