//
// Created by Yeloki on 09.05.2022.
//

#ifndef CONTAINERS_EXCEPTIONS_LIST_H
#define CONTAINERS_EXCEPTIONS_LIST_H

#include "exception.h"


/// Array exceptions
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

/// Queue exceptions
#define QUEUE_IS_EMPTY  \
  ((struct SxTraceEntry) {300, 0, __FILE__, __LINE__, "\0", NULL})
#define QUEUE_NODE_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {301, 0, __FILE__, __LINE__, "\0", NULL})
#define QUEUE_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {302, 0, __FILE__, __LINE__, "\0", NULL})

/// Stack exceptions
#define STACK_IS_EMPTY  \
  ((struct SxTraceEntry) {303, 0, __FILE__, __LINE__, "\0", NULL})
#define STACK_NODE_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {304, 0, __FILE__, __LINE__, "\0", NULL})
#define STACK_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {305, 0, __FILE__, __LINE__, "\0", NULL})


#endif //CONTAINERS_EXCEPTIONS_LIST_H
