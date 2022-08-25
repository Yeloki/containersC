//
// Created by Yeloki on 03.05.2022.
//

#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include "../array/array.h"

#define NIL &sentinel
rbtree_node sentinel = {NIL, NIL, 0, BLACK, 0};

tree *createTree() {
  tree *new_tree = malloc(sizeof(tree));
  rbtree_node *new = NIL;
  new_tree->root = new;
  new_tree->is_unique = true;
  return new_tree;
}

void deleteRBTree(tree *t) {
  tree_iterator *iterator = createTreeIterator(t, t->root);
  while (!iterator->end)
    free(treeIteratorNext(iterator));
  deleteTreeIterator(iterator);
  free(t);
}

void rotateLeft(tree *t, rbtree_node *n) {
  rbtree_node *y = n->right;
  n->right = y->left;
  if (y->left != NIL)
    y->left->parent = n;
  if (y != NIL)
    y->parent = n->parent;
  if (n->parent) {
    if (n == n->parent->left)
      n->parent->left = y;
    else
      n->parent->right = y;
  } else {
    t->root = y;
  }
  y->left = n;
  if (n != NIL)
    n->parent = y;
}

void rotateRight(tree *t, rbtree_node *n) {
  rbtree_node *y = n->left;

  /* establish n->left link */
  n->left = y->right;
  if (y->right != NIL) y->right->parent = n;

  /* establish y->parent link */
  if (y != NIL) y->parent = n->parent;
  if (n->parent) {
    if (n == n->parent->right)
      n->parent->right = y;
    else
      n->parent->left = y;
  } else {
    t->root = y;
  }
  y->right = n;
  if (n != NIL) n->parent = y;
}

void insertFixup(tree *t, rbtree_node *x) {
  while (x != t->root && x->parent->color == RED) {
    if (x->parent == x->parent->parent->left) {
      rbtree_node *y = x->parent->parent->right;
      if (y->color == RED) {
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      } else {
        if (x == x->parent->right) {
          x = x->parent;
          rotateLeft(t, x);
        }
        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rotateRight(t, x->parent->parent);
      }
    } else {
      rbtree_node *y = x->parent->parent->left;
      if (y->color == RED) {
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      } else {
        if (x == x->parent->left) {
          x = x->parent;
          rotateRight(t, x);
        }
        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rotateLeft(t, x->parent->parent);
      }
    }
  }
  t->root->color = BLACK;
}

rbtree_node *insertNode(tree *t, rbtree_val val) {
  rbtree_node *current, *parent, *x;
  current = t->root;
  parent = 0;
  while (current != NIL) {
    if (t->is_unique && compEQ(val, current->val)) return (current);
    parent = current;
    current = compLT(val, current->val) ?
              current->left : current->right;
  }
  if ((x = malloc(sizeof(rbtree_node))) == 0)
    throw(RBTREE_NODE_MEMORY_ALLOCATION_ERROR);
  x->val = val;
  x->parent = parent;
  x->left = NIL;
  x->right = NIL;
  x->color = RED;
  if (parent) {
    if (compLT(val, parent->val))
      parent->left = x;
    else
      parent->right = x;
  } else {
    t->root = x;
  }

  insertFixup(t, x);
  return (x);
}

void deleteFixup(tree *t, rbtree_node *x) {
  while (x != t->root && x->color == BLACK) {
    if (x == x->parent->left) {
      rbtree_node *w = x->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateLeft(t, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rotateRight(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        rotateLeft(t, x->parent);
        x = t->root;
      }
    } else {
      rbtree_node *w = x->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateRight(t, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          rotateLeft(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rotateRight(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = BLACK;
}

void deleteTreeNode(tree *t, rbtree_val val) {
  rbtree_node *z = findNode(t, val);
  if (z == NULL)
    throw(RBTREE_NODE_DOES_NOT_EXIST);
  rbtree_node *x, *y;
  if (!z || z == NIL)
    return;
  if (z->left == NIL || z->right == NIL) {
    y = z;
  } else {
    y = z->right;
    while (y->left != NIL)
      y = y->left;
  }
  if (y->left != NIL)
    x = y->left;
  else
    x = y->right;
  x->parent = y->parent;
  if (y->parent)
    if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;
  else
    t->root = x;
  if (y != z)
    z->val = y->val;
  if (y->color == BLACK)
    deleteFixup(t, x);
  free(y);
}

rbtree_node *findNode(tree *t, rbtree_val val) {
  rbtree_node *current = t->root;
  while (current != NIL)
    if (compEQ(val, current->val))
      return current;
    else
      current = compLT (val, current->val) ?
                current->left : current->right;
  return NULL;
}

void fillTreeIterator__(tree_iterator *iterator, rbtree_node *from) {
  if (from == NIL) return;
  fillTreeIterator__(iterator, from->left);
  pushToQueue(iterator->q, from);
  fillTreeIterator__(iterator, from->right);
}

tree_iterator *createTreeIterator(tree *t, rbtree_node *from) {
  tree_iterator *iterator = malloc(sizeof(tree_iterator));
  iterator->t = t;
  iterator->q = createQueue();
  fillTreeIterator__(iterator, from);
  iterator->end = false;
  return iterator;
}

void deleteTreeIterator(tree_iterator *iterator) {
  deleteQueue(iterator->q);
  free(iterator);
}

rbtree_node *treeIteratorNext(tree_iterator *iterator) {
  rbtree_node *n = ((rbtree_node *) popFromQueue(iterator->q));
  if (queueIsEmpty(iterator->q))
    iterator->end = true;
  return n;
}

void fillReversedTreeIterator__(reversed_tree_iterator *iterator, rbtree_node *from) {
  if (from == NIL) return;
  fillReversedTreeIterator__(iterator, from->left);
  pushToStack(iterator->s, from);
  fillReversedTreeIterator__(iterator, from->right);
}

reversed_tree_iterator *createReversedTreeIterator(tree *t, rbtree_node *from) {
  reversed_tree_iterator *iterator = malloc(sizeof(reversed_tree_iterator));
  iterator->t = t;
  iterator->s = createStack();
  fillReversedTreeIterator__(iterator, t->root);
  return iterator;
}

void deleteReversedTreeIterator(reversed_tree_iterator *iterator) {
  deleteStack(iterator->s);
  free(iterator);
}

rbtree_node *reversedTreeIteratorNext(reversed_tree_iterator *iterator) {
  rbtree_node *n = ((rbtree_node *) popFromStack(iterator->s));
  if (stackIsEmpty(iterator->s))
    iterator->end = true;
  return n;
}

void print_right_part(rbtree_node *root, int v, array *arr);

void print_left_part(rbtree_node *root, int v, array *arr) {
  if (root == NIL) {
    arrayDestroy(arr);
    return;
  }
  array *arrN = arrayInit(), *arrO = arrayInit();
  for (int i = 0; i < arraySize(arr); ++i) {
    arrayPushBackChar(arrN, arrayAtChar(arr, i));
    arrayPushBackChar(arrO, arrayAtChar(arr, i));
  }
  char s[8] = " |      ";
  for (int i = 0; i < 8; ++i)
    arrayPopBackChar(arrN);
  for (int i = 0; i < 8; ++i)
    arrayPushBackChar(arrN, ' ');
  for (int i = 0; i < 8; ++i) {
    arrayPushBackChar(arrN, s[i]);
    arrayPushBackChar(arrO, s[i]);
  }
  print_right_part(root->right, v + 1, arrO);
  for (int i = 0; i < arraySize(arr) - 8; ++i)
    printf("%c", arrayAtChar(arr, i));
  printf(" \\----->");
  print_val(root->val);
  printf("\n");
  print_left_part(root->left, v + 1, arrN);
  arrayDestroy(arr);
}

void print_right_part(rbtree_node *root, int v, array *arr) {
  if (root == NIL) {
    arrayDestroy(arr);
    return;
  }
  array *arrN = arrayInit(), *arrO = arrayInit();
  for (int i = 0; i < arraySize(arr); ++i) {
    arrayPushBackChar(arrN, arrayAtChar(arr, i));
    arrayPushBackChar(arrO, arrayAtChar(arr, i));
  }
  char s[8] = " |      ";
  for (int i = 0; i < 8; ++i)
    arrayPopBackChar(arrN);
  for (int i = 0; i < 8; ++i)
    arrayPushBackChar(arrN, ' ');
  for (int i = 0; i < 8; ++i) {
    arrayPushBackChar(arrN, s[i]);
    arrayPushBackChar(arrO, s[i]);
  }
  print_right_part(root->right, v + 1, arrN);
  for (int i = 0; i < arraySize(arr) - 8; ++i)
    printf("%c", arrayAtChar(arr, i));
  printf(" /----->");
  print_val(root->val);
  printf("\n");
  print_left_part(root->left, v + 1, arrO);
  arrayDestroy(arr);
}

void print_root(rbtree_node *root) {
  if (root == NIL) return;
  array *arrL = arrayInit(), *arrR = arrayInit();
  char s[8] = " |      ";
  for (int i = 0; i < 8; ++i) {
    arrayPushBackChar(arrL, s[i]);
    arrayPushBackChar(arrR, s[i]);
  }
  print_right_part(root->right, 0, arrR);
  print_val(root->val);
  printf("\n");
  print_left_part(root->left, 0, arrL);
}

void printRBTree(tree *t) {
  if (t->root != NIL)
    print_root(t->root);
  else
    printf("TREE IS EMPTY\n");
}

size_t leaf_count(rbtree_node *n) {
  if (n->left == NIL && n->right == NIL)
    return 0;
  if (n->left != NIL && n->right != NIL)
    return 2;
  return 1;
}

rbtree_val parse() {
  char s[8];
  int code = scanf("%s", s);
  if (code == EOF)
    throw(NOT_ERR_EOF__);
  if (isEqual(s, "ZERO"))
    return ZERO;
  else if (isEqual(s, "ONE"))
    return ONE;
  else if (isEqual(s, "TWO"))
    return TWO;
  else if (isEqual(s, "THREE"))
    return THREE;
  else if (isEqual(s, "FOUR"))
    return FOUR;
  else if (isEqual(s, "FIVE"))
    return FIVE;
  else if (isEqual(s, "SIX"))
    return SIX;
  else if (isEqual(s, "SEVEN"))
    return SEVEN;
  else if (isEqual(s, "EIGHT"))
    return EIGHT;
  else if (isEqual(s, "NINE"))
    return NINE;
  else if (isEqual(s, "TEN"))
    return TEN;
  else
    throw(RBTREE_PARSE_ERROR);
}

void print_val(rbtree_val v) {
  switch (v) {
    case ZERO:printf("ZERO");
      break;
    case ONE:printf("ONE");
      break;
    case TWO:printf("TWO");
      break;
    case THREE:printf("THREE");
      break;
    case FOUR:printf("FOUR");
      break;
    case FIVE:printf("FIVE");
      break;
    case SIX:printf("SIX");
      break;
    case SEVEN:printf("SEVEN");
      break;
    case EIGHT:printf("EIGHT");
      break;
    case NINE:printf("NINE");
      break;
    case TEN:printf("TEN");
      break;

  }
}

bool isEqual(const char *s1, const char *s2) {
  size_t i = 0;
  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i])
      return false;
    ++i;
  }
  return s1[i] == s2[i];
}