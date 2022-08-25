//
// Created by Yeloki on 03.05.2022.
//

#ifndef LAB_23_RBTREE_H
#define LAB_23_RBTREE_H

#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include "../stack/stack.h"
#include "../queue/queue.h"
#include "../exception/exception.h"

#define RBTREE_IS_EMPTY  \
  ((struct SxTraceEntry) {300, 0, __FILE__, __LINE__, "\0", NULL})
#define RBTREE_NODE_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {301, 0, __FILE__, __LINE__, "\0", NULL})
#define RBTREE_MEMORY_ALLOCATION_ERROR  \
  ((struct SxTraceEntry) {302, 0, __FILE__, __LINE__, "\0", NULL})
#define RBTREE_NODE_DOES_NOT_EXIST  \
  ((struct SxTraceEntry) {302, 0, __FILE__, __LINE__, "\0", NULL})
#define NOT_ERR_EOF__ \
    ((struct SxTraceEntry) {310, 0, __FILE__, __LINE__, "\0", NULL})
#define RBTREE_PARSE_ERROR \
          ((struct SxTraceEntry) {320, 0, __FILE__, __LINE__, "\0", NULL})
//typedef int rbtree_val;

typedef enum {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN
} rbtree_val;

rbtree_val parse();

void print_val(rbtree_val);

#define compLT(a, b) ((a) < (b))
#define compEQ(a, b) ((a) == (b))

typedef enum {
    BLACK,
    RED,
} rbtreeNodeColor;

typedef struct rbtree_node_ {
    struct rbtree_node_ *left;
    struct rbtree_node_ *right;
    struct rbtree_node_ *parent;
    rbtreeNodeColor color;
    rbtree_val val;
} rbtree_node;

typedef struct {
    rbtree_node *root;
    bool is_unique;
} tree;

tree *createTree();

void rotateLeft(tree *, rbtree_node *n);

void rotateRight(tree *, rbtree_node *n);

void insertFixup(tree *, rbtree_node *x);

rbtree_node *insertNode(tree *, rbtree_val val);

void deleteFixup(tree *, rbtree_node *x);

void deleteTreeNode(tree *t, rbtree_val);

rbtree_node *findNode(tree *, rbtree_val val);

typedef struct {
    tree *t;
    queue *q;
    bool end;
} tree_iterator;

void fillTreeIterator__(tree_iterator *iterator, rbtree_node *from);

tree_iterator *createTreeIterator(tree *t, rbtree_node *from);

void deleteTreeIterator(tree_iterator *iterator);

rbtree_node *treeIteratorNext(tree_iterator *iterator);

typedef struct {
    tree *t;
    stack *s;
    bool end;
} reversed_tree_iterator;

void fillReversedTreeIterator__(reversed_tree_iterator *iterator, rbtree_node *from);

reversed_tree_iterator *createReversedTreeIterator(tree *t, rbtree_node *from);

void deleteReversedTreeIterator(reversed_tree_iterator *iterator);

rbtree_node *reversedTreeIteratorNext(reversed_tree_iterator *iterator);

void printRBTree(tree *t);

void deleteRBTree(tree *t);

size_t leaf_count(rbtree_node *n);

bool isEqual(const char *s1, const char *s2);

#endif //LAB_23_RBTREE_H
