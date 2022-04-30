//
// Created by Yeloki on 25.04.2022.
//

#include "array.h"
#include <assert.h>


void arrayInit(array *arr) {
    arr->size = 0;
    arr->capacity = 2;
    arr->_min_capacity = 2;
    arr->data = malloc(arr->capacity * sizeof(array_el));
    if (arr->data == NULL)
        throw(ARRAY_MEMORY_ALLOCATION_ERROR);
}

void arrayResize(array *arr, size_t n_size) {
    arr->data = realloc(arr->data, n_size * sizeof(array_el));
    if (arr->data == NULL)
        throw(ARRAY_MEMORY_ALLOCATION_ERROR);
    for (size_t i = arr->size; i < n_size; ++i)
        arr->data[i] = 0;
    arr->capacity = n_size;
}

void arrayPushBack(array *arr, array_el el) {
    if (arr->size == arr->capacity)
        arrayResize(arr, arr->capacity * 2);
    arr->data[(arr->size)++] = el;
}

void arrayDestroy(array *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

array_el *arrayData(array *arr) {
    return arr->data;
}

array_el arrayAt(array *arr, size_t index) {
    if (index >= arr->size)
        throw(ARRAY_INDEX_OUT_OF_RANGE);
    return arr->data[index];
}

array_el *arrayGet(array *arr, size_t index) {
    if (index >= arr->size)
        throw(ARRAY_INDEX_OUT_OF_RANGE);
    return &(arr->data[index]);
}

array_el arrayFront(array *arr) {
    return arr->data[0];
}

array_el arrayBack(array *arr) {
    return arr->data[arr->size - 1];
}

array_iter *arrayBegin(array *arr) {
    return arrayIterInIt(arr, arr->data);
}

array_iter *arrayEnd(array *arr) {
    return arrayIterInIt(arr, arr->data + arr->size);
}

bool arrayEmpty(array *arr) {
    return !arr->size;
}

size_t arraySize(array *arr) {
    return arr->size;
}

size_t arrayCapacity(array *arr) {
    return arr->capacity;
}

void arrayClear(array *arr) {
    free(arr->data);
    arr->data = calloc(arr->_min_capacity, sizeof(array_el));
    arr->size = 0;
    arr->capacity = arr->_min_capacity;
}

array_el *arrayInsert(array *arr, size_t index, array_el el) {
    if (index >= arr->size)
        throw(ARRAY_INDEX_OUT_OF_RANGE);
    if (arr->size == arr->capacity)
        arrayResize(arr, arr->capacity * 2);

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

void arrayErase(array *arr, array_el el) {
    array_el *temp = calloc(arr->capacity, sizeof(array_el));
    size_t n_size = 0;
    for (size_t i = 0; i < arr->size; ++i)
        if (arr->data[i] != el)
            temp[n_size++] = arr->data[i];
    free(arr->data);
    arr->data = temp;
    arr->size = n_size;
    if (arr->size < arr->capacity / 2)
        arrayResize(arr, arr->capacity / 2);
}

array_el arrayPopBack(array *arr) {
    if (arr->size == 0)
        throw(ARRAY_IS_EMPTY);
    array_el el = arr->data[--arr->size];
    if (arr->size < arr->capacity / 2)
        arrayResize(arr, arr->capacity / 2);
    return el;
}

void arrayShrinkToFit(array *arr) {
    if (arr->size <= arr->_min_capacity)
        arrayResize(arr, arr->_min_capacity);
    else
        arrayResize(arr, arr->size);
}

#ifdef DEBUG

void arrayTestAll() {
    {
        /// test push_back, resize and at
        array array1;
        arrayInit(&array1);
        for (size_t el = 0; el < 100; ++el)
            arrayPushBack(&array1, (double) el);
        assert(arraySize(&array1) == 100);
        for (int i = 0; i < 100; ++i) {
            assert((double) i == arrayAt(&array1, i));
        }
        assert(arrayCapacity(&array1) == 128);
        arrayDestroy(&array1);
    }
    {
        /// test throw index error
        array array1;
        arrayInit(&array1);
        arrayResize(&array1, 64);
        bool flag = 0;
        try {
            arrayGet(&array1, 64);
        } catch(ARRAY_INDEX_OUT_OF_RANGE.code) {
            flag = true;
        }
        endtry
        assert(flag);
        arrayDestroy(&array1);
    }
    {
        /// test throw memory allocation error
        array array1;
        arrayInit(&array1);
        arrayResize(&array1, 64);
        bool flag = 0;
        try {
            arrayResize(&array1, (size_t) 1e18);
        } catch(ARRAY_MEMORY_ALLOCATION_ERROR.code) {
            flag = true;
        }
        endtry
        assert(flag);
        arrayDestroy(&array1);
    }
    {
        /// test front, back, get, empty & clear
        array array1;
        arrayInit(&array1);
        for (size_t i = 50; i < 100; ++i)
            arrayPushBack(&array1, (double) i);
        assert(arrayFront(&array1) == 50);
        assert(arrayBack(&array1) == 99);
        assert(*arrayGet(&array1, 22) == arrayAt(&array1, 22));
        assert(!arrayEmpty(&array1));
        arrayClear(&array1);
        assert(arrayEmpty(&array1));
    }
    {
        /// test data, shrink_to_fit
        array array1;
        arrayInit(&array1);
        for (size_t i = 0; i < 100; ++i)
            arrayPushBack(&array1, (double) i);
        assert(arrayData(&array1) == array1.data);
        arrayShrinkToFit(&array1);
        assert(array1.capacity == array1.size);
        arrayDestroy(&array1);
    }
    {
        /// test insert
        array array1;
        arrayInit(&array1);
        for (size_t i = 0; i < 100; ++i)
            arrayPushBack(&array1, (double) i);
        arrayInsert(&array1, 20, 104);
        assert(array1.size == 101);
        assert(*arrayGet(&array1, 20) == 104);
        arrayDestroy(&array1);
    }
    {
        /// test erase & arrayPopBack
        array array1;
        arrayInit(&array1);
        for (size_t i = 0; i < 100; ++i)
            arrayPushBack(&array1, (double) i);
        for (size_t i = 1; i < 100; i += 5)
            arrayInsert(&array1, i, 20);
        arrayErase(&array1, 20);
        assert(array1.size == 99);
        assert(arrayPopBack(&array1) == 99);
        assert(array1.size == 98);
        arrayDestroy(&array1);
    }
}

#endif