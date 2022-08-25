//
// Created by Yeloki on 30.04.2022.
//

#ifndef CONTAINERS_ARRAY_TOOLS_H
#define CONTAINERS_ARRAY_TOOLS_H

#include "array.h"
#include <assert.h>

void arrayReverse(array_iter *begin, array_iter *end) {
  while (arrayIterIsNotEqual(begin, end)) {
    array_el tmp = *arrayIterCurr(begin);
    *arrayIterCurr(begin) = *arrayIterPrev(end);
    *arrayIterCurr(end) = tmp;
    arrayIterNext(begin);
  }
  arrayIterDestroy(begin);
  arrayIterDestroy(end);
}

void arraySort(array_iter *begin, array_iter *end) {
  arrayIterDestroy(begin);
  arrayIterDestroy(end);
}

#ifdef DEBUG
//
//void arrayToolsTestAll() {
//  {
//    array *array1 = arrayInit(), *array2 = arrayInit();
//
//    for (int i = 0; i < 100; ++i) {
//      arrayPushBack(array1, i);
//      arrayPushBack(array2, 99 - i);
//    }
//    arrayReverse(arrayBegin(array2), arrayEnd(array2));
//    for (int i = 0; i < 100; ++i)
//      assert(arrayAt(array1, i) == arrayAt(array2, i));
//  }
//}

#endif //DEBUG

#endif //CONTAINERS_ARRAY_TOOLS_H
