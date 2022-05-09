//
// Created by Yeloki on 06.05.2022.
//

#include "stack.h"
#include <malloc.h>

stack *createStack() {
    stack *new = malloc(sizeof(stack));
    /// Если не получилось выделить память - бросаем исключение
    if (new == NULL)
        throw(STACK_MEMORY_ALLOCATION_ERROR);
    new->first = NULL;
    new->last = NULL;
    new->size = 0;
    return new;
}

bool stackIsEmpty(stack *s) {
    return s->size == 0;
}

void pushToStack(stack *s, stack_val v) {
    stack_node *new = malloc(sizeof(stack_node));
    /// Если не получилось выделить память - бросаем исключение
    if (new == NULL)
        throw(STACK_NODE_MEMORY_ALLOCATION_ERROR);
    if (stackIsEmpty(s)) {
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

stack_val popFromStack(stack *s) {
    /// Если пытаемся взять элемент из пустого стека - бросаем исключение
    if (stackIsEmpty(s))
        throw(STACK_IS_EMPTY);
    stack_val v = s->last->val;
    stack_node *node = s->last;
    if (s->last != s->first) {
        s->last = node->next;
        node->next->prev = NULL;
    } else {
        s->first = NULL;
        s->last = NULL;
    }
    free(node);
    --s->size;
    return v;
}

void deleteStack(stack *s) {
    /// Если стек не пустой - очищаем его
    while (!stackIsEmpty(s))
        popFromStack(s);
    free(s);
}

