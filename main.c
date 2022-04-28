
#include <stdio.h>
#include "array/array.h"


int main() {
    array_test_all();
    array array1;
    array_init(&array1);
    for (double el = 0; el < 100; el += 1)
        array_push_back(&array1, el);
    array_destroy(&array1);
    return 0;
}
