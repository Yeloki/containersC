//
// Created by Yeloki on 08.05.2022.
//

#ifndef LAB_23_QUEUE_H
#define LAB_23_QUEUE_H

#include "../exception/exceptions_list.h"
#include <stdbool.h>

typedef void* queue_val;

typedef struct queue_node {
    struct queue_node *prev;
    struct queue_node *next;
    queue_val val;
} queue_node;


typedef struct queue {
    queue_node *first;
    queue_node *last;
    size_t size;
} queue;

queue *createQueue();

void pushToQueue(queue *s, queue_val v);

queue_val popFromQueue(queue *s);

void deleteQueue(queue *s);

bool queueIsEmpty(queue *s);


#endif //LAB_23_QUEUE_H
