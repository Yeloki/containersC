//
// Created by Yeloki on 08.05.2022.
//

#include "queue.h"

queue *createQueue() {
    queue *new = malloc(sizeof(queue));
    /// Если не получилось выделить память - бросаем исключение
    if (new == NULL)
        throw(QUEUE_MEMORY_ALLOCATION_ERROR);
    new->first = NULL;
    new->last = NULL;
    new->size = 0;
    return new;
}

bool queueIsEmpty(queue *s) {
    return s->size == 0;
}

void pushToQueue(queue *s, queue_val v) {
    queue_node *new = malloc(sizeof(queue_node));
    /// Если не получилось выделить память - бросаем исключение
    if (new == NULL)
        throw(QUEUE_NODE_MEMORY_ALLOCATION_ERROR);
    if (queueIsEmpty(s)) {
        s->first = new;
        s->last = new;
        new->next = NULL;
        new->prev = NULL;
    } else {
        new->next = s->last;
        new->prev = NULL;
        s->last->prev = new;
        s->last = new;
    }
    new->val = v;
    ++s->size;
}

queue_val popFromQueue(queue *s) {
    /// Если пытаемся взять элемент из пустой очереди - бросаем исключение
    if (queueIsEmpty(s))
        throw(QUEUE_IS_EMPTY);
    queue_val v = s->first->val;
    queue_node *node = s->first;
    if (s->last != s->first) {
        s->first = node->prev;
        node->prev->next = NULL;
    } else {
        s->first = NULL;
        s->last = NULL;
    }
    free(node);
    --s->size;
    return v;
}

void deleteQueue(queue *s) {
    /// Если очередь не пустая - очищаем её
    while (!queueIsEmpty(s))
        popFromQueue(s);
    free(s);
}
