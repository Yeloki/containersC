#include "rbtree/rbtree.h"
#include "array/array.h"
/// var 9

void solve(tree *t) {
  size_t ans = 0;
  tree_iterator *iter = createTreeIterator(t, t->root);
  while (!iter->end) {
    rbtree_node *n = treeIteratorNext(iter);
    if (n->val == leaf_count(n))
      ans++;
  }
  printf("The number of vertices whose value is the same as its own degree: %lu\n", ans);
}

void help() {
  printf((
             "Using:\n"
             "h - call this message\n"
             "a <value> - add value to tree\n"
             "p - print tree\n"
             "d <value> - delete ONE node with current value\n"
             "s - call the \"solve\" function of variant 9\n"
             "f - fill the tree with 10000 of random elements\n"
             "q - quit the program\n"
             "Possible values:\n"
             "ZERO, ONE, TWO, THREE, FOUR, FIVE\n"
             "SIX, SEVEN, EIGHT, NINE, TEN\n"
         ));
}


bool clear() {
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
  return c == EOF;
}

void print_possible_values() {
  printf((
             "This value doesn't support, possible values:\n"
             "ZERO, ONE, TWO, THREE, FOUR, FIVE\n"
             "SIX, SEVEN, EIGHT, NINE, TEN\n"
         ));
}

int main(int argc, char **argv) {
  tree *t = createTree();
  t->is_unique = false;
  int value;
  while (true) {
    char command[20];
    int code = scanf("%s", command);
    if (code == EOF) return 0;
    if (isEqual(command, "h")) {
      help();
    } else if (isEqual(command, "a")) {
      try {
        value = parse();
        insertNode(t, value);
      } catch(NOT_ERR_EOF__.code) {
        return 0;
      } catch(RBTREE_PARSE_ERROR.code) {
        print_possible_values();
      }
      endtry
    } else if (isEqual(command, "p")) {
      printRBTree(t);
    } else if (isEqual(command, "d")) {
      try {
        value = parse();
        deleteTreeNode(t, value);
      } catch(NOT_ERR_EOF__.code) {
        return 0;
      } catch(RBTREE_PARSE_ERROR.code) {
        print_possible_values();
      } catch(RBTREE_NODE_DOES_NOT_EXIST.code) {
        printf("Node with value %d doesn't exists\n", value);
      }
      endtry
    } else if (isEqual(command, "s")) {
      solve(t);
    } else if (isEqual(command, "q")) {
      break;
    } else if (isEqual(command, "f")) {
      for (int i = 0; i < 1000; ++i) {
        int k = rand() % 10;
        insertNode(t, k);
      }
    } else
      printf("Wrong command, type \"h\" to get info\n");
    if (clear())
      return 0;
  }
  deleteRBTree(t);
  return 0;
}